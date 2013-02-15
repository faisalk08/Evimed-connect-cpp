/*
 * EvimedSearchModel.h
 *
 *  Created on: Feb 14, 2013
 *      Author: indra
 */

#ifndef EVIMEDSEARCHMODEL_H_
#define EVIMEDSEARCHMODEL_H_
#include <iostream>
#include <list>
#include <EvimedModel.h>
#include <../header/JSONUtil.h>
using namespace std;
using namespace util;

namespace model {

class EvimedSearchModel {
public:
	EvimedSearchModel();
	EvimedSearchModel(string data);

	list<EvimedModel> getResults();
	EvimedModel* getInfo();

	virtual ~EvimedSearchModel();
private:
	list<EvimedModel> results;
	EvimedModel* info;

	EvimedModel loopData(ptree tree, string arrayName);
	void loopArrayData(string data, list<EvimedModel>* listModel, string arrayName);
	void loopData(string data, EvimedModel* model, string arrayName);
};

} /* namespace model */
#endif /* EVIMEDSEARCHMODEL_H_ */
