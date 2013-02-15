/*
 * JSONUtil.h
 *
 *  Created on: Feb 11, 2013
 *      Author: indra
 */

#ifndef JSONUTIL_H_
#define JSONUTIL_H_
#include <iostream>
#include <map>
#include <list>
using namespace std;
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <EvimedModel.h>
using namespace boost::property_tree;
using namespace model;

namespace util {

class JSONUtil {
public:
	//JSONUtil();

	static string getJSONString(string data, string key);
	static string getJSONValue(string data, string key);
	static list <string> getJSONArrayValue(string data, string arrayName, string key);
	static map <string, string> getJSONPair(string data);
	static map <string, string> getJSONPair(string data, string arrayName);
	static list <map<string, string> > getJSONArrayPair(string data, string arrayName);
	static list <map<string, string> > getJSONArrayPair(string data);
	static string readJsonValue(string jsonData, string key);
	static void loopArrayData(string data, list<EvimedModel>* listModel, string arrayName);
	//virtual ~JSONUtil();

private:

};

} /* namespace util */
#endif /* JSONUTIL_H_ */
