/*
 * OAuthClient.cpp
 *
 *  Created on: Dec 19, 2012
 *      Author: indra
 */

#include <../header/OAuthClient.h>

namespace oauth {
static string slash = "/";
static string ampersand = "&";
static string questionMark = "?";

OAuthClient::OAuthClient(){

}

OAuthClient::OAuthClient(string eConf, string uConf){

	cout << "Construct" << endl;
	//Read config files
	read_ini(eConf, pevimedConfig);
	read_ini(uConf, puserConfig);

	try {
		serverUrl  = pevimedConfig.get<string>("evimed.server_url");
	} catch (exception& e) {
		string error = "Error on this description: ";
		error.append(e.what());
		cout <<  error << endl;
		return;
	}

	loadingConfiguration(serverUrl, eConf, uConf);
}

OAuthClient::OAuthClient(string url, string eConf, string uConf){
	loadingConfiguration(url, eConf, uConf);
}

void OAuthClient::loadingConfiguration(string url, string eConf, string uConf){
	consumer = NULL;
	client = NULL;
	init = false;
	authenticated = false;

	eConfig = eConf;
	uConfig = uConf;
	serverUrl = url;

	if(serverUrl.empty()) throw 1; // if server URL empty throw an error

	//Read config files
	//if(pevimedConfig.empty() || puserConfig.empty()){
		//cout << "read it again" + puserConfig.empty() << endl;
//		read_ini(eConfig, pevimedConfig);
//		read_ini(uConfig, puserConfig);
	//}

	try {
		//Get all service URLs from the Evimed Config file
		request_token_url = pevimedConfig.get<string>("evimed.request_token_url");
		access_token_url = pevimedConfig.get<string>("evimed.access_token_url");
		authorize_url = pevimedConfig.get<string>("evimed.authorize_url");
		logout_url = pevimedConfig.get<string>("evimed.logout_url");

		//Get all Evimed APIs
		//patient_url = pevimedConfig.get<string>("evimed.api_patient_url");
	//			trialsearch_url = pevimedConfig.get<string>("evimed.api_trialsearch_url");
	//			trialrecruitment_url = pevimedConfig.get<string>("evimed.api_trialrecruitment_url");
	//			trialrecruitment_match_url = pevimedConfig.get<string>("evimed.api_trialrecruitment_match_url");
	//			trialrecruitment_status_url = pevimedConfig.get<string>("evimed.api_trialrecruitment_status_url");
		profile_url = pevimedConfig.get<string>("evimed.api_profile_url");

		cout << "Checking configuration Urls " + request_token_url << endl;

		if(initialize()) init = true;

	} catch (exception& e) {
		string error = "Error on this description: ";
		error.append(e.what());
		cout <<  error << endl;
		return;
	}
}

bool OAuthClient::initialize(){
	cout << "Initialize" << endl;
	if(consumer!=0) {delete consumer;	consumer = NULL;}
	if(client!=0) {delete client;	client = NULL;}

	//Get the Consumer Key and Secret from Evimed config
	consumerKey = pevimedConfig.get<string>("evimed.consumerKey");
	consumerSecret = pevimedConfig.get<string>("evimed.consumerSecret");
	consumer = new Consumer(consumerKey, consumerSecret);

	//Try to get the OAuth key and secret from User config
	oauth_key = puserConfig.get<string>("user.oauth_key", "");
	oauth_secret = puserConfig.get<string>("user.oauth_secret", "");
	//Try to get User Information
	emailAddress = puserConfig.get<string>("user.emailAddress", "");

	if(initClient(oauth_key, oauth_secret)) {
		authenticated = authenticate();
		return true;
	}

	return false;
}

bool OAuthClient::isAuthenticated(){
	return authenticated;
}

bool OAuthClient::authenticate(){
	cout << "Authenticate" << endl;
	string url = serverUrl + profile_url;
	string query = questionMark + "website=pm";

	url+= query;
	string response = getData(url);

	if(response.empty()) return false;

	cout << "response profile " + response << endl;

	emailAddress = JSONUtil::readJsonValue(response, "emailAddress");
	puserConfig.put("user.emailAddress", emailAddress);

	return true;
}

bool OAuthClient::initClient(string oauth_key, string oauth_secret){
	cout << "Init Client" << endl;

	if(client!=NULL){
		delete client; client = NULL;
	}

	if(!oauth_secret.empty() && !oauth_key.empty()){ //If the Oauth Key and Secret are in the User config
		token = new Token(oauth_key, oauth_secret);
		client = new Client(consumer, token);
		return true;
	}else{
		client = new Client(consumer);
		return false;
	}

}

/*string OAuthClient::getQuery(map<string, string> params){

	iterate
	url + params.
	getQuery(url, true);

	return queryString;
}*/

string OAuthClient::getQuery(string url, bool withPin){
	cout << "query GET url " + url << endl;

	if(client==0) cout << "client is empty" << endl;
	string queryString = client->getURLQueryString(OAuth::Http::Get, url, "", withPin);

	return queryString;
}

string OAuthClient::postQuery(string url, bool withPin){
	cout << "query POST url " + url << endl;

	if(client==0) cout << "client is empty" << endl;
	string queryString = client->getURLQueryString(OAuth::Http::Post, url, "", withPin);

	return queryString;
}

string OAuthClient::request(){
	if(init) initClient(); else initialize();

	cout << "Requesting" << endl;
	string url = serverUrl + request_token_url;
	string queryString = getQuery(url, true);
	url = url + questionMark + queryString;

	string response = httpClient.get(url);

	Token response_token = Token::extract(response);
	initClient(response_token.key(), response_token.secret());

	response = serverUrl + authorize_url + questionMark + response;
	//authorize_url = response;
	cout << "response " + response<< endl;
	return response;
}

string OAuthClient::authorize(string userName, string password){
	string query = "emailAddress=" + userName + "&password=" + password;
	string response = httpClient.post(serverUrl + authorize_url, query, true);
	cout << "response: " + response << endl;
	return response;
}

string OAuthClient::access(){
	string url = serverUrl + access_token_url;
	cout << "accessing" << endl;
	string queryString = getQuery(url);

	url = url + questionMark + queryString;
	cout << " url " + url<< endl;

	string response = httpClient.get(url, true);
	cout << "response " + response << endl;

	Token response_token = Token::extract(response);

	init = initClient(response_token.key(), response_token.secret());
	authenticated = authenticate();
	puserConfig.put("user.oauth_key", response_token.key());
	puserConfig.put("user.oauth_secret", response_token.secret());
	write_ini(uConfig, puserConfig);

	return response;
}

string OAuthClient::getData(string url){

	string urlSigned;
	string response;

	urlSigned = getSignedUrl(url);

	cout << "url Signed " + urlSigned<< endl;
	response = httpClient.get(urlSigned);
	cout << "Response " + response << endl;

	//If the response contains any of these sentences than return unsuccessfully attempt
	if(response.find("This request requires HTTP authentication")!=string::npos || response.find("Login with your existing Evimed.com user name and password!")!=string::npos){
//				logout();//try to logout from previous key and secret
		return "";
	}

	return response;

}

string OAuthClient::getData(string url, string &signedUrl){

	string urlSigned;
	string response;

	urlSigned = getSignedUrl(url);

	cout << "url Signed " + urlSigned<< endl;
	signedUrl = urlSigned;
	response = httpClient.get(urlSigned);
	cout << "Response " + response << endl;

	//If the response contains any of these sentences than return unsuccessfully attempt
	if(response.find("This request requires HTTP authentication")!=string::npos || response.find("Login with your existing Evimed.com user name and password!")!=string::npos){
//				logout();//try to logout from previous key and secret
		return "";
	}

	return response;

}

string OAuthClient::postData(string url, string data){

	string urlSigned;
	string response;

	urlSigned = getSignedUrl(url, true);

	cout << " url Signed " + urlSigned<< endl;
	response = httpClient.post(urlSigned, data);
	cout << "Response " + response << endl;

	//If the response contains any of these sentences than return unsuccessfully attempt
	if(response.find("This request requires HTTP authentication")!=string::npos ||
			response.find("Login with your existing Evimed.com user name and password!")!=string::npos){
//				logout();//try to logout previous key and secret
		return "";
	}

	return response;

}

string OAuthClient::getSignedUrl(string url, bool post){
//			cout << "Get URL signed" << endl;

	string urlSigned="";
	string parameter;
	size_t pos = url.find(questionMark);

	string query;
	if(post)
		query = postQuery(url, true);
	else
		query = getQuery(url, true);

	if(pos!=string::npos){ // if '?' found
		parameter = url.substr(pos+1, url.size()-1);
		url = url.substr(0,pos);
	}

	urlSigned = url + questionMark + query;

	return urlSigned;
}

string OAuthClient::logout(){

	cout << "ERASE" << endl;
	puserConfig.clear();
	puserConfig.put("user.oauth_key" , "");
	puserConfig.put("user.oauth_secret" , "");
	write_ini(uConfig, puserConfig);

	if(!init) return "";

	string url = serverUrl + logout_url;
	cout << "logout" << endl;
	string queryString = getQuery(url, true);
	url = url + questionMark + queryString;

	string response = httpClient.get(url);
	cout << "response " + response << endl;

	authenticated = false;
	init = false;

	return response;
}

}

