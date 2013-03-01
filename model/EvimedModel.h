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
#include <JSONUtil.h>
using namespace std;
using namespace util;

namespace model {

class EvimedModel {
public:
	EvimedModel();
	EvimedModel(map <string, string> data);

	void put(string key, string value);
	void put(string key, EvimedModel model);
	string get(string key);
	void remove(string key);
	void update(string key, string value);

	map<string, string> getMap();

	string toString();

	virtual ~EvimedModel();
private:
	map<string, string> mapModel;
};

} /* namespace model */
#endif /* EVIMEDMODEL_H_ */
