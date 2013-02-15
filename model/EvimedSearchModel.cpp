/*
 * EvimedSearchModel.cpp
 *
 *  Created on: Feb 14, 2013
 *      Author: indra
 */

#include "EvimedSearchModel.h"

namespace model {

EvimedSearchModel::EvimedSearchModel() {
	// TODO Auto-generated constructor stub

}

EvimedSearchModel::EvimedSearchModel(string data) {

	loopArrayData(data, &results, "result");
	loopData(data, info, "info");
}

list<EvimedModel> EvimedSearchModel::getResults(){
	return results;
}

EvimedModel* EvimedSearchModel::getInfo(){
	return info;
}

void EvimedSearchModel::loopArrayData(string data, list<EvimedModel>* listModel, string arrayName){
	list<map<string, string> > listResult = JSONUtil::getJSONArrayPair(data, arrayName);
	for (list<map<string, string> >::iterator it = listResult.begin(); it != listResult.end(); ++it) {
		/*for(map<string, string>::iterator im=it->begin();im!=it->end();++im){
			cout << im->first << endl;
		}*/

		listModel->push_front(EvimedModel(*it));
	}
}

void EvimedSearchModel::loopData(string data, EvimedModel* model, string arrayName){
	model = new EvimedModel(JSONUtil::getJSONPair(data, arrayName));
}

EvimedModel EvimedSearchModel::loopData(ptree tree, string arrayName){
//	EvimedModel model;
//	for (ptree::iterator it = tree.begin(); it != tree.end(); ++it) {
//		string key(it->first.data());
//		string value(it->second.data());
//
//		if(key==arrayName)
//			model = loopData(it->second, "");
//		else
//			model.put(key, value);
//	}
//
//	return model;
}

EvimedSearchModel::~EvimedSearchModel() {
	// TODO Auto-generated destructor stub
}

} /* namespace model */
