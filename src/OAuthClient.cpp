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

		OAuthClient::OAuthClient(string url){
			cout << "Initialize" << endl;
			request_token_url = "/oauth/request_token";
			access_token_url = "/oauth/access_token";
			authorize_url = "/oauth/authorize";
			logout_url = "/oauth/logout";
			consumer = NULL;
			client = NULL;

			if(url.empty()) throw 1;

			serverUrl = url;

		}

		void OAuthClient::initialize(){
			if(consumer!=0) {delete consumer;	consumer = NULL;}
			if(client!=0) {delete client;	client = NULL;}

			consumerKey = "html5TestConsumer";
			consumerSecret = "html5TestAPIOAuthKey";

			consumer = new Consumer(consumerKey, consumerSecret);
			client = new Client(consumer);
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
			initialize();

			string url = serverUrl + request_token_url;
			cout << "Requesting" << endl;
			string queryString = getQuery(url, false);
			url = url + "?" + queryString;

			string response = httpClient.get(url);

			Token response_token = Token::extract(response);
			token = new Token(response_token.key(), response_token.secret());

			delete client;	client = NULL;

			client = new Client(consumer, token);

			cout << "response " + response<< endl;
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
			token = new Token(response_token.key(), response_token.secret());
			delete client; client = NULL;

			client = new Client(consumer, token);

			return response;
		}

		string OAuthClient::getData(string url){
			string queryString = getQuery(url, true);

			url = url + "?" + queryString;
			cout << " url " + url<< endl;
			string response = httpClient.get(url);
			return response;

		}

		string OAuthClient::logout(){
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

