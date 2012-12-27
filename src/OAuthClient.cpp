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

		OAuthClient::OAuthClient(string url, string eConf, string uConf){
			cout << "Construct" << endl;

			eConfig = eConf;
			uConfig = uConf;

			read_ini(eConfig, evimedConfig);
			read_ini(uConfig, userConfig);

			request_token_url = evimedConfig.get<string>("evimed.request_token_url");
			access_token_url = evimedConfig.get<string>("evimed.access_token_url");
			authorize_url = evimedConfig.get<string>("evimed.authorize_url");
			logout_url = evimedConfig.get<string>("evimed.logout_url");

			consumer = NULL;
			client = NULL;
			init = false;

			if(url.empty()) throw 1;

			serverUrl = url;

			if(initialize()) init = true;

		}

		bool OAuthClient::initialize(){
			cout << "Initialize" << endl;
			if(consumer!=0) {delete consumer;	consumer = NULL;}
			if(client!=0) {delete client;	client = NULL;}

			consumerKey = evimedConfig.get<string>("evimed.consumerKey");
			consumerSecret = evimedConfig.get<string>("evimed.consumerSecret");

			consumer = new Consumer(consumerKey, consumerSecret);

			string oauth_key = userConfig.get<string>("user.oauth_key", "");
			string oauth_secret = userConfig.get<string>("user.oauth_secret", "");
			if(initClient(oauth_key, oauth_secret)) return true;

			return false;
		}

		bool OAuthClient::initClient(string oauth_key, string oauth_secret){
			cout << "Init Client" << endl;

			if(client!=NULL){
				delete client; client = NULL;
			}

			if(!oauth_secret.empty() && !oauth_key.empty()){
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

			string url = serverUrl + request_token_url;
			cout << "Requesting" << endl;
			string queryString = getQuery(url, false);
			url = url + "?" + queryString;

			string response = httpClient.get(url);

			Token response_token = Token::extract(response);
			initClient(response_token.key(), response_token.secret());

			cout << "response " + response<< endl;
			response = serverUrl + authorize_url + "?" + response;
			return response;
		}

		string OAuthClient::access(){
			string url = serverUrl + access_token_url;
			cout << "accessing" << endl;
			string queryString = getQuery(url, true);

			url = url + "?" + queryString;
			cout << " url " + url<< endl;

			string response = httpClient.get(url);
			cout << "response " + response << endl;

			Token response_token = Token::extract(response);
			init = initClient(response_token.key(), response_token.secret());

			userConfig.put("user.oauth_key", response_token.key());
			userConfig.put("user.oauth_secret", response_token.secret());
			write_ini(uConfig, userConfig);

			return response;
		}

		string OAuthClient::getData(string url, bool automatically){

			string urlSigned;
			string response;

			//Get url Signed from user properties
			urlSigned = userConfig.get("user." + url, "");
			if(urlSigned.empty()) {

				urlSigned = getSignedUrl(url);

			}

			cout << " url Signed " + urlSigned<< endl;
			response = httpClient.get(urlSigned);
			cout << "Response " + response << endl;

			if(response.find("This request requires HTTP authentication")!=string::npos){
				logout();//try to logout previous key and secret
				return "";
			}


			return response;

		}

		string OAuthClient::getSignedUrl(string url){
			string urlSigned;
			cout << " url Signed is Empty" << endl;
			string append ="?";
			string parameter;
			size_t pos = url.find(append);

			if(pos!=string::npos){ // if '?' found
				parameter = url.substr(pos+1, url.size()-1);
				url = url.substr(0,pos);
			}

			string query = getQuery(url, false);

			if(parameter.empty())
				urlSigned = url + append + query;
			else
				urlSigned = url + append + query + "&" + parameter;

			userConfig.put("user." + url, urlSigned);
			write_ini(uConfig, userConfig);

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
			url = url + "?" + queryString;
			cout << " url " + url<< endl;
			string response = httpClient.get(url);
			cout << "response " + response << endl;

			return response;
		}


		}
	}
	}
}

