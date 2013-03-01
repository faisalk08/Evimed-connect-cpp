/*
 * OAuthClient.h
 *
 *  Created on: Feb 11, 2013
 *      Author: indra
 */

#ifndef OAUTHCLIENT_H_
#define OAUTHCLIENT_H_
#include <iostream>
#include <HttpClient.h>
#include <JSONUtil.h>
#include <exception>
#include <liboauthcpp.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>

using namespace std;
using namespace util;
using namespace OAuth;
using namespace boost::property_tree;

namespace oauth {

class OAuthClient {
public:
	OAuthClient();
	OAuthClient(string serverUrl, string evimedConfig, string userConfig);
	OAuthClient(string evimedConfig, string userConfig);
	void loadingConfiguration(string serverUrl, string evimedConfig, string userConfig);
	string request();
	string authorize(string userName, string password);
	string access();
	string getData(string url);
	string getData(string url, string &signedUrl);
	string postData(string url, string data);
	string putData(string url, string data);
	string deleteData(string url);
	string getSignedUrl(string url, bool post=false, bool remove=false, bool put=false);
	string logout();
	string serverUrl;
	bool isAuthenticated();

private:
	string consumerKey;
	string consumerSecret;
	Token *token;
	Consumer *consumer;
	Client *client;
	HttpClient httpClient;

	bool initialize();
	bool initClient(string oauth_key = "", string oauth_secret = "");
	string getQuery(string url, bool withPin=false);
	string postQuery(string url, bool withPin=false);
	string deleteQuery(string url, bool withPin=false);
	string putQuery(string url, bool withPin=false);
	//string readJsonValue(string jsonData, string key);

	string request_token_url;
	string access_token_url;
	string authorize_url;
	string logout_url;
	string signedParameter;
	string oauth_key;
	string oauth_secret;

	ptree pevimedConfig;
	ptree puserConfig;

	//ptree evimedConfig;
	//ptree userConfig;
	string eConfig;
	string uConfig;
	bool init;
	bool authenticated;
	bool authenticate();

	string profile_url;
	string emailAddress;
};


}

#endif /* OAUTHCLIENT_H_ */
