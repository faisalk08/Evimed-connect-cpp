/*
 * HttpClient.h
 *
 *  Created on: Dec 10, 2012
 *      Author: indra
 */

#ifndef HTTPCLIENT_H_
#define HTTPCLIENT_H_

#include <iostream>
#include <curl/curl.h>
using namespace std;

class HttpClient {
public:

	string get(string url);
	string post(string url, string query);

private:

};


#endif /* HTTPCLIENT_H_ */
