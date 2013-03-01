/*
 * HttpClient.cpp
 *
 *  Created on: Dec 19, 2012
 *      Author: indra
 */

#include "../header/HttpClient.h"

namespace util {


struct WriteThis {
  const char *readptr;
  int sizeleft;
};

size_t write_response(char *ptr, size_t size, size_t nmemb, string *stream){
	if(ptr!=NULL){
		stream->append(ptr, size * nmemb);
		return size * nmemb;
	}

	return 0;
}

size_t read_response(char *ptr, size_t size, size_t nmemb, string *userp){
/*	if(ptr!=NULL){
		userp->append(ptr, size * nmemb);
		return size * nmemb;
	}*/

	struct WriteThis *response = (struct WriteThis*) userp;

	if (size*nmemb < 1)
		return 0;

	if(response->sizeleft){
		*(char *)ptr = response->readptr[0];
		response->readptr++;
		response->sizeleft--;
		return 1;
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
//		snprintf(nline, sizeof(nline),"cookie=test");
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

string HttpClient::remove(string url){
	CURL *curl;
	CURLcode code;
	string content = "";

	curl = curl_easy_init();
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1 );
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

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
	struct curl_slist *headers = NULL;
	string content = "";

	struct WriteThis pooh;
//	query = "{\"patientId\":7318,\"trialId\":7919,\"comments\":\"\",\"trialCenterCode\":\"rene\",\"contactPhone\":\"\",\"contactAddress\":\"\",\"contactEmail\":\"evimed@evimed.com\"}";
	const char *data= query.c_str();
	pooh.readptr = data;
	pooh.sizeleft = (long) strlen(data);

//	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "charsets: utf-8");
//	headers = curl_slist_append(headers, "Transfer-Encoding: chunked");
//	headers = curl_slist_append(headers, "Expect:");

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl){
//		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
//		if(!query.empty())
//			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());
//		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
//		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_response);
		curl_easy_setopt(curl, CURLOPT_READDATA, &pooh);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, pooh.sizeleft);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//		if(write)
//		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookie.txt");
//		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookie.txt");
//		else
//		curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1 );
//		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1 );

		code = curl_easy_perform(curl);
		if(code!=CURLE_OK)
			fprintf(stderr, "perform failed: %s\n", curl_easy_strerror(code));

		curl_easy_cleanup(curl);

	}
	curl_global_cleanup();
	return content;
}

string HttpClient::put(string url, string query){
	cout << "HTTP Post" << endl;

	CURL *curl;
	CURLcode code;
	struct curl_slist *headers = NULL;
	string content = "";

	struct WriteThis pooh;
	const char *data= query.c_str();
	pooh.readptr = data;
	pooh.sizeleft = (long) strlen(data);

	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "charsets: utf-8");

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_PUT, 1L);
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_response);
		curl_easy_setopt(curl, CURLOPT_READDATA, &pooh);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, pooh.sizeleft);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		code = curl_easy_perform(curl);
		if(code!=CURLE_OK)
			fprintf(stderr, "perform failed: %s\n", curl_easy_strerror(code));

		curl_easy_cleanup(curl);

	}
	curl_global_cleanup();
	return content;
}

}  // namespace util

