/*
 * EvimedConfig.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: indra
 */

#include "EvimedConfig.h"

namespace model {

EvimedConfig::EvimedConfig(){

}

EvimedConfig::EvimedConfig(string filePath, bool autoSave){

	this->autoSave = autoSave;
	this->filePath = filePath;

	read_ini(this->filePath, config);

	try {
		mapConfig = convert(config);
	} catch (exception& e) {
		string error = "Error on this description: ";
		error.append(e.what());
		cout <<  error << endl;
		return;
	}

}

map<string, string> EvimedConfig::convert(ptree config, string root){

	for (ptree::const_iterator it = config.begin(); it!=config.end() ; ++it) {
//		cout << it->first << endl;
//		cout << it->second.get_value<string>() << endl;

		if(it->second.get_value<string>()=="")
			convert(it->second, string(it->first.data()));

		string key(it->first.data());
		string value(it->second.data());
		if(value!=""){
			key = root + "." + key;
			mapConfig.insert(pair<string, string>(key, value));
			cout << key + " : " + value << endl;
		}

	}

	return mapConfig;
}

map<string, string> EvimedConfig::getMapConfig(){
	return mapConfig;
}


string EvimedConfig::get(string key){
	return config.get<string>(key);
}

void EvimedConfig::put(string key, string value){
	config.put(key, value);
	if(autoSave) write();
}

void EvimedConfig::write(){
	write_ini( this->filePath, config);
}

EvimedConfig::~EvimedConfig() {
	// TODO Auto-generated destructor stub
}

} /* namespace model */
