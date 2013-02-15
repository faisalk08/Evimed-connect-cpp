/*
 * EvimedModel.h
 *
 *  Created on: Feb 13, 2013
 *      Author: indra
 */

#ifndef EVIMEDMODEL_H_
#define EVIMEDMODEL_H_
#include <iostream>
#include <map>
using namespace std;
namespace model {

class EvimedModel {
public:
	EvimedModel();
	EvimedModel(map <string, string> data);

	void put(string key, string value);
	string get(string key);

	map<string, string> getMap();

	virtual ~EvimedModel();
private:
	map<string, string> mapModel;
};

} /* namespace model */
#endif /* EVIMEDMODEL_H_ */
