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

namespace util {

class HttpClient {
public:

	string get(string url, bool write=false);
	string post(string url, string query="", bool write=false);

private:

};

}  // namespace util

#endif /* HTTPCLIENT_H_ */
