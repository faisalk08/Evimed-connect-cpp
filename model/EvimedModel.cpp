/*
 * EvimedModel.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: indra
 */

#include "EvimedModel.h"

namespace model {


EvimedModel::EvimedModel() {
	// TODO Auto-generated constructor stub
}

EvimedModel::EvimedModel(map<string, string> data) {
	// TODO Auto-generated constructor stub
	this->mapModel = data;
}

void EvimedModel::put(string key, string value){
	mapModel.insert(pair<string, string>(key, value));
}

string EvimedModel::get(string key){
	return string(mapModel.find(key)->second);
}

map<string, string> EvimedModel::getMap(){
	return mapModel;
}

EvimedModel::~EvimedModel() {
	// TODO Auto-generated destructor stub
}

} /* namespace model */
