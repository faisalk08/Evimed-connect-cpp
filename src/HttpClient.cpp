/*
 * HttpClient.cpp
 *
 *  Created on: Dec 19, 2012
 *      Author: indra
 */

#include <HttpClient.h>

static size_t write_response(char *ptr, size_t size, size_t nmemb, string *stream){
	if(ptr!=NULL){
		stream->append(ptr, size * nmemb);
		return size * nmemb;
	}

	return 0;
}

string HttpClient::get(string url, bool write){
	CURL *curl;
	CURLcode code;
	string content = "";
//	char nline[2048];
//	struct curl_slist *headers=NULL;

	curl = curl_easy_init();
	if(curl){
//		curl_slist_append(headers, "Authorization:  oauth_nonce=1276107867blah");
//		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookie.txt");
//		snprintf(nline, sizeof(nline),
//				"connect.sid=s%3Ajrh7AGw2VaPWn%2Fkvlk9t4joZ.JLfPyW7ue7bxZuEVejS4GkT5y7n%2BqQk56SUeTLl2%2FP4; "
//				"path=/; "
//				"_isEcho=false; "
//				"_consumerKey=esystem; "
//				"access_token=4d816ddbc8821682d55c37016d2b01b2; "
//				"access_token_secret=1c8b983aa018aafa847edaee1e2aa427; "
//				"_requestUrl=http://staging.evimed.com/oauth/request_token; "
//				"_accessUrl=http://staging.evimed.com/oauth/access_token; "
//				"_consumerSecret=846963-ESYSTEM; "
//				"_version=1.0; "
//				"_authorize_callback=http://localhost:9745/oauth/callback; "
//				"_signatureMethod=HMAC-SHA1; "
//				"_nonceSize=32; "
//				"_oauthParameterSeperator= ',' ; "
//				"loginUrl=http://localhost:9745/oauth/login; "
//				"logoutUrl=http://localhost:9745/oauth/logout; "
//				"successUrl=/erm/; "
//				"authorizeUrl=http://staging.evimed.com/oauth/authorize; "
//				"authorizedAccessUrl=http://staging.evimed.com/oauth/authorized_token; "
//				"loggedIn=true; "
//			);
//		curl_easy_setopt(curl, CURLOPT_COOKIE, nline);
//		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);


//		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookie.txt");
//		curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1 );
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1 );

		code = curl_easy_perform(curl);

		if(code!=CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s \n", curl_easy_strerror(code));
		}

		curl_easy_cleanup(curl);
	}

	return content;
}

string HttpClient::post(string url, string query, bool write){
	cout << "HTTP Post" << endl;

	CURL *curl;
	CURLcode code;
	struct curl_slist *headers=NULL;
	string content = "";

	curl_slist_append(headers, "Accept: application/json");
	curl_slist_append(headers, "Content-Type: application/json");
	curl_slist_append(headers, "charsets: utf-8");

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl){
//		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		if(!query.empty())
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
//		if(write)
//		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookie.txt");
//		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookie.txt");
//		else

//		curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1 );
//		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1 );

		code = curl_easy_perform(curl);
		if(code!=CURLE_OK)
			fprintf(stderr, "perform failed: %s\n", curl_easy_strerror(code));

//		curl_easy_cleanup(curl);

	}
	curl_global_cleanup();
	return content;
}

