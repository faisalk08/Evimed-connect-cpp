/*
 * evimedconnect.h
 *
 *  Created on: Dec 19, 2012
 *      Author: indra
 */

#ifndef EVIMEDCONNECT_H_
#define EVIMEDCONNECT_H_
#if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#endif

#include <iostream>
#include <liboauthcpp.h>
#include <HttpClient.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <QtWebKit/QWebView>
#include <WebView.h>

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
					string authorize(string userName, string password);
					string access();
					string getData(string url);
					string getData(string url, string &signedUrl);
					string getSignedUrl(string url, bool post=false);
					string logout();
					string serverUrl;
					bool isAuthenticated();
					string postData(string url, string data);

					string getPatient(int patientId=0);
					string getTrialRecruitment(int patientId, int trialId);
					string getTrialRecruitmentStatus(int patientId);
					string getTrialRecruitmentWithId(int recruitmentId);
					string postTrialRecruitment(int patientId, int trialId, string centerCode, string contactAddress="", string contactPhone="", string comment="");
					string searchTrial(int patientId, int start=0, int end=5, string trialParameters="type%3D1");

					list<string> getJSONValue(string data, string arrayName, string key);
					map<string, string> getJSONPair(string data, string arrayName);

					QWebView* getWebView();
					QWebView* webView;

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
					string readJsonValue(string jsonData, string key);

					string request_token_url;
					string access_token_url;
					string authorize_url;
					string logout_url;
					string signedParameter;
					string oauth_key;
					string oauth_secret;

					ptree evimedConfig;
					ptree userConfig;
					string eConfig;
					string uConfig;
					bool init;
					bool authenticated;
					bool authenticate();

					string profile_url;
					string patient_url;
					string trialrecruitment_url;
					string trialrecruitment_match_url;
					string trialrecruitment_status_url;
					string trialsearch_url;

					string emailAddress;

				};



		}  // namespace Evimedwrapper

		}  // namespace portal

	}  // namespace evimed

}  // namespace com


#endif /* EVIMEDCONNECT_H_ */
