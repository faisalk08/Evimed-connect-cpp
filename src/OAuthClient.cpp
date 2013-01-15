/*
 * OAuthClient.cpp
 *
 *  Created on: Dec 19, 2012
 *      Author: indra
 */

#include <evimedConnect.h>

namespace com {

	namespace evimed {

	namespace portal {

		namespace EvimedConnect {

		static string slash = "/";
		static string ampersand = "&";
		static string questionMark = "?";

		OAuthClient::OAuthClient(string url, string eConf, string uConf){

			consumer = NULL;
			client = NULL;
			init = false;

			eConfig = eConf;
			uConfig = uConf;
			serverUrl = url;

			if(serverUrl.empty()) throw 1; // if server URL empty throw an error

			//Read config files
			read_ini(eConfig, evimedConfig);
			read_ini(uConfig, userConfig);

			//Get all the service URLs from the Evimed Config file
			request_token_url = evimedConfig.get<string>("evimed.request_token_url");
			access_token_url = evimedConfig.get<string>("evimed.access_token_url");
			authorize_url = evimedConfig.get<string>("evimed.authorize_url");
			logout_url = evimedConfig.get<string>("evimed.logout_url");

			patient_url = evimedConfig.get<string>("evimed.api_patient_url");
			trialsearch_url = evimedConfig.get<string>("evimed.api_trialsearch_url");
			trialrecruitment_url = evimedConfig.get<string>("evimed.api_trialrecruitment_url");
			trialrecruitment_match_url = evimedConfig.get<string>("evimed.api_trialrecruitment_match_url");
			profile_url = evimedConfig.get<string>("evimed.api_profile_url");

			cout << "Checking configuration Urls " + request_token_url << endl;

			if(initialize()) init = true;

		}

		bool OAuthClient::initialize(){
			cout << "Initialize" << endl;
			if(consumer!=0) {delete consumer;	consumer = NULL;}
			if(client!=0) {delete client;	client = NULL;}

			//Get the Consumer Key and Secret from Evimed config
			consumerKey = evimedConfig.get<string>("evimed.consumerKey");
			consumerSecret = evimedConfig.get<string>("evimed.consumerSecret");
			consumer = new Consumer(consumerKey, consumerSecret);

			//Try to get the OAuth key and secret from User config
			oauth_key = userConfig.get<string>("user.oauth_key", "");
			oauth_secret = userConfig.get<string>("user.oauth_secret", "");

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
			string url = serverUrl + profile_url;
			string response = getData(url);

			if(response.empty()) return false;

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

		string OAuthClient::getQuery(string url, bool withPin){
			cout << "query url " + url << endl;

			if(client==0)
				cout << "client is empty" << endl;
			string queryString = client->getURLQueryString(OAuth::Http::Get, url, "", withPin);

			cout << "end url " << endl;
			return queryString;
		}

		string OAuthClient::request(){
			if(init) initClient();

			cout << "Requesting" << endl;
			string url = serverUrl + request_token_url;
			string queryString = getQuery(url, true);
			url = url + questionMark + queryString;

			string response = httpClient.get(url);

			Token response_token = Token::extract(response);
			initClient(response_token.key(), response_token.secret());

			response = serverUrl + authorize_url + questionMark + response;
			authorize_url = response;
			cout << "response " + response<< endl;
			return response;
		}

		string OAuthClient::authorize(string userName, string password){
			string query = "emailAddress=" + userName + "&password=" + password;
			string response = httpClient.post(authorize_url, query, true);
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

			userConfig.put("user.oauth_key", response_token.key());
			userConfig.put("user.oauth_secret", response_token.secret());
			write_ini(uConfig, userConfig);

			return response;
		}

		string OAuthClient::getData(string url){

			string urlSigned;
			string response;

			//Get url Signed from user properties
//			urlSigned = userConfig.get("user." + url, "");
//			if(urlSigned.empty()) {

				urlSigned = getSignedUrl(url);

//			}

			cout << " url Signed " + urlSigned<< endl;
			response = httpClient.get(urlSigned);
			cout << "Response " + response << endl;

			//If the response contains any of these sentences than return unsuccessfully attempt
			if(response.find("This request requires HTTP authentication")!=string::npos || response.find("Login with your existing Evimed.com user name and password!")!=string::npos){
//				logout();//try to logout previous key and secret
				return "";
			}


			return response;

		}

		string OAuthClient::postData(string url, string data){

			string urlSigned;
			string response;

			urlSigned = getSignedUrl(url);

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

		string OAuthClient::getSignedUrl(string url){
			cout << "Get URL signed" << endl;

			string urlSigned="";
			string append ="?";
			string ampersand = "&";
			string parameter;
			size_t pos = url.find(append);


			string query = getQuery(url, true);
			cout << "query " + query << endl;

			if(pos!=string::npos){ // if '?' found
				parameter = url.substr(pos+1, url.size()-1);
				url = url.substr(0,pos);
			}
			/*if(parameter.empty())
				urlSigned = url + append + query;
			else
				urlSigned = url + append + query + ampersand + parameter;*/

			urlSigned = url + append + query;

//			userConfig.put(p, urlSigned);
//			write_ini(uConfig, userConfig);

//			cout << "URL signed " + urlSigned << endl;

			return urlSigned;
		}

		string OAuthClient::logout(){

			cout << "ERASE" << endl;
			userConfig.clear();
			userConfig.put("user.oauth_key" , "");
			userConfig.put("user.oauth_secret" , "");
			write_ini(uConfig, userConfig);

			if(!init) return "";

			string url = serverUrl + logout_url;
			cout << "logout" << endl;
			string queryString = getQuery(url, true);
			url = url + questionMark + queryString;

			cout << " url " + url<< endl;
			string response = httpClient.get(url);
			cout << "response " + response << endl;

			return response;
		}


		string OAuthClient::getPatient(int patientId){
			string url;
			stringstream id;
			id << patientId;
			if(patientId==0)
				url = serverUrl + patient_url;
			else
				url = serverUrl + patient_url + slash + id.str();

			string response = getData(url);

			return response;

		}


		string OAuthClient::searchTrial(int patientId, int start, int end, string trialParameters){
			string url;
			stringstream id, s, e;
			id << patientId; s << start; e << end;

			url = serverUrl + trialsearch_url + slash + id.str() + questionMark + "start=" + s.str() + ampersand + "end=" + e.str() + ampersand + "trialParameters=" + trialParameters;
			cout<< url << endl;
			string response = getData(url);

			return response;

		}

		string OAuthClient::postTrialRecruitment(int patientId, int trialId){
			string url;
			stringstream id, tId;
			id << patientId; tId << trialId;

			url = serverUrl + trialrecruitment_url;
			string data = "patientId=" + id.str() + ampersand + "trialId=" + tId.str() + ampersand + "emailAddress=evimed@evimed.com" + ampersand + "trialCenterCode=Goettingen";
			string response = postData(url, data);

			return response;
		}

		string OAuthClient::getTrialRecruitment(int patientId, int trialId){
			string url;
			stringstream id, tId;
			id << patientId; tId << trialId;

			url = serverUrl + trialrecruitment_match_url;
			string query = questionMark + "patientId=" + id.str() + ampersand + "trialId=" + tId.str() + ampersand + "website=pm";

			url+= query;

			cout << url << endl;

			string response = getData(url);

			return response;
		}
	}
	}
	}
}

