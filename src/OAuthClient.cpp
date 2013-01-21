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
			authenticated = false;

			eConfig = eConf;
			uConfig = uConf;
			serverUrl = url;

			if(serverUrl.empty()) throw 1; // if server URL empty throw an error

			//Read config files
			read_ini(eConfig, evimedConfig);
			read_ini(uConfig, userConfig);

			//Get all service URLs from the Evimed Config file
			request_token_url = evimedConfig.get<string>("evimed.request_token_url");
			access_token_url = evimedConfig.get<string>("evimed.access_token_url");
			authorize_url = evimedConfig.get<string>("evimed.authorize_url");
			logout_url = evimedConfig.get<string>("evimed.logout_url");

			//Get all Evimed APIs
			patient_url = evimedConfig.get<string>("evimed.api_patient_url");
			trialsearch_url = evimedConfig.get<string>("evimed.api_trialsearch_url");
			trialrecruitment_url = evimedConfig.get<string>("evimed.api_trialrecruitment_url");
			trialrecruitment_match_url = evimedConfig.get<string>("evimed.api_trialrecruitment_match_url");
			trialrecruitment_status_url = evimedConfig.get<string>("evimed.api_trialrecruitment_status_url");
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
			//Try to get User Information
			emailAddress = userConfig.get<string>("user.emailAddress", "");

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

			emailAddress = readJsonValue(response, "emailAddress");
			userConfig.put("user.emailAddress", emailAddress);

			return true;
		}

		string OAuthClient::readJsonValue(string jsonData, string key){
			ptree jsonResponse;
			stringstream s(jsonData);
			read_json(s, jsonResponse);

			string value = jsonResponse.get<string>(key);

			return value;
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
			authenticated = authenticate();
			userConfig.put("user.oauth_key", response_token.key());
			userConfig.put("user.oauth_secret", response_token.secret());
			write_ini(uConfig, userConfig);

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
			userConfig.clear();
			userConfig.put("user.oauth_key" , "");
			userConfig.put("user.oauth_secret" , "");
			write_ini(uConfig, userConfig);

			if(!init) return "";

			string url = serverUrl + logout_url;
			cout << "logout" << endl;
			string queryString = getQuery(url, true);
			url = url + questionMark + queryString;

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
			string response = getData(url);

			return response;

		}

		string OAuthClient::postTrialRecruitment(int patientId, int trialId, string centerCode, string contactAddress, string contactPhone, string comment){
			string url;
			stringstream id, tId;
			id << patientId; tId << trialId;

			url = serverUrl + trialrecruitment_url;
			string query = questionMark + "website=pm";
			url+=query;
//			string data = "patientId=" + id.str() + ampersand + "trialId=" + tId.str() + ampersand + "emailAddress=" + ampersand + "trialCenterCode=";

			ptree jsonData;
			jsonData.put("patientId", patientId);
			jsonData.put("trialId", trialId);
			jsonData.put("contactEmail", emailAddress);
			jsonData.put("trialCenterCode", centerCode);
			jsonData.put("comments", comment);
			jsonData.put("contactPhone", contactPhone);
			jsonData.put("contactAddress", contactAddress);
			stringstream ss;
			write_json(ss, jsonData);

			string response = postData(url, ss.str());

			return response;
		}

		string OAuthClient::getTrialRecruitment(int patientId, int trialId){
			string url;
			stringstream id, tId;
			id << patientId; tId << trialId;

			url = serverUrl + trialrecruitment_match_url;
			string query = questionMark + "patientId=" + id.str() + ampersand + "trialId=" + tId.str() + ampersand + "website=pm";

			url+= query;

			string response = getData(url);

			return response;
		}

		string OAuthClient::getTrialRecruitmentStatus(int patientId){
			string url;
			stringstream id, tId;
			id << patientId;

			url = serverUrl + trialrecruitment_status_url;
			string query = questionMark + "patientId=" + id.str() + ampersand + "website=pm";

			url+= query;

			string response = getData(url);

			return response;
		}

		string OAuthClient::getTrialRecruitmentWithId(int recruitmentId){
			string url;
			stringstream id, tId;
			id << recruitmentId;

			url = serverUrl + trialrecruitment_url;
			string query = slash + id.str() + questionMark + "website=pm";

			url+= query;

			string response = getData(url);

			return response;
		}

		list<string> OAuthClient::getJSONValue(string data, string arrayName, string key){
			stringstream s(data);
			ptree JsonResponse;
			read_json(s, JsonResponse);

			list<string> listValue;
			BOOST_FOREACH(ptree::value_type &child, JsonResponse.get_child(arrayName)){
//				cout << child.second.empty() << endl;
				if(child.first.empty())
					listValue.push_front(child.second.get<string>(key));
				else
					listValue.push_front(child.second.data());
			}

			return listValue;
		}

		map<string, string> OAuthClient::getJSONPair(string data, string arrayName){
			stringstream s(data);
			ptree JsonResponse;
			read_json(s, JsonResponse);

			map<string, string> mapKeyValue;
			BOOST_FOREACH(ptree::value_type &child, JsonResponse.get_child(arrayName)){

				string f(child.first.data());
				string s(child.second.data());

				mapKeyValue.insert(pair<string, string>(f, s));

			}

			return mapKeyValue;
		}

	}
	}
	}
}

