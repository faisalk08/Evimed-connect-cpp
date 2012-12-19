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

string HttpClient::get(string url){
	CURL *curl;
	CURLcode code;
	string content = "";

	curl = curl_easy_init();
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);

		code = curl_easy_perform(curl);

		if(code!=CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s \n", curl_easy_strerror(code));
		}

		curl_easy_cleanup(curl);
	}

	return content;
}

string HttpClient::post(string url, string query){
	cout << "HTTP Post" << endl;

	CURL *curl;
	CURLcode code;
	struct curl_slist *headers=NULL;
	string content = "";

	curl_slist_append(headers, "Accept: application/json");
	curl_slist_append(headers, "Content-Type: application/json");
	curl_slist_append(headers, "charsets: utf-8");

	curl = curl_easy_init();
	if(curl){
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);

		code = curl_easy_perform(curl);
		if(code!=CURLE_OK)
			fprintf(stderr, "perform failed: %s\n", curl_easy_strerror(code));

		curl_easy_cleanup(curl);

	}

	return content;
}

