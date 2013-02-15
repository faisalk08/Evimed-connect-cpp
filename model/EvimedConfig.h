/*
 * EvimedConfig.h
 *
 *  Created on: Feb 13, 2013
 *      Author: indra
 */

#ifndef EVIMEDCONFIG_H_
#define EVIMEDCONFIG_H_
#include <iostream>
#include <map>
#include <iterator>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
using namespace std;

using namespace boost::property_tree;

namespace model {

class EvimedConfig {
public:
	EvimedConfig();
	EvimedConfig(string filePath, bool autoSave);

	string get(string key);
	void put(string key, string value);
	void write();
	map<string, string> getMapConfig();

	virtual ~EvimedConfig();
private:
	ptree config;
	bool autoSave;
	string filePath;
	map<string, string > mapConfig;
	map<string, string> convert(ptree config, string root="");
};

} /* namespace model */
#endif /* EVIMEDCONFIG_H_ */
