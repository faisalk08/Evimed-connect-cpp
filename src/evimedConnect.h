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

using namespace std;
using namespace OAuth;

namespace com {

	namespace evimed {

		namespace portal {

		namespace EvimedConnect {

			class OAuthClient {
				public:
					OAuthClient(string serverUrl);
					string request();
					string access();
					string getData(string url);
					string signedUrl(string url);
					string logout();
					string serverUrl;

				private:
					string consumerKey;
					string consumerSecret;
					Token *token;
					Consumer *consumer;
					Client *client;
					HttpClient httpClient;

					void initialize();
					string getQuery(string url, bool withPin=false);

					string request_token_url;
					string access_token_url;
					string authorize_url;
					string logout_url;

				};



		}  // namespace Evimedwrapper

		}  // namespace portal

	}  // namespace evimed

}  // namespace com


#endif /* EVIMEDCONNECT_H_ */
