/*
 * evimedconnect.h
 *
 *  Created on: Dec 19, 2012
 *      Author: indra
 */

#ifndef EVIMEDCONNECT_H_
#define EVIMEDCONNECT_H_

#include <iostream>
#include <liboauthcpp.h>
#include <HttpClient.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

using namespace std;
using namespace OAuth;
using namespace boost::property_tree;

namespace com {

	namespace evimed {

		namespace portal {

		namespace EvimedConnect {

			class OAuthClient {
				public:
					OAuthClient(string serverUrl, string evimedConfig, string userConfig);
					string request();
					string access();
					string getData(string url, bool automatically=false);
					string getSignedUrl(string url);
					string logout();
					string serverUrl;


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

					string request_token_url;
					string access_token_url;
					string authorize_url;
					string logout_url;
					string signedParameter;

					ptree evimedConfig;
					ptree userConfig;
					string eConfig;
					string uConfig;
					bool init;

				};



		}  // namespace Evimedwrapper

		}  // namespace portal

	}  // namespace evimed

}  // namespace com


#endif /* EVIMEDCONNECT_H_ */
