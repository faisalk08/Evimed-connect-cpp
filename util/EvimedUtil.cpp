/*
 * EvimedUtil.cpp
 *
 *  Created on: Feb 22, 2013
 *      Author: indra
 */

#include "EvimedUtil.h"

namespace util {

EvimedUtil::EvimedUtil() {
	// TODO Auto-generated constructor stub

}

void EvimedUtil::loopArrayData(string data, list<EvimedModel>* listModel, string arrayName){
	list<map<string, string> > listResult;
	if(arrayName=="")
		listResult = JSONUtil::getJSONArrayPair(data);
	else
		listResult = JSONUtil::getJSONArrayPair(data, arrayName);

	for (list<map<string, string> >::iterator it = listResult.begin(); it != listResult.end(); ++it) {
		listModel->push_front(EvimedModel(*it));
	}
}

EvimedUtil::~EvimedUtil() {
	// TODO Auto-generated destructor stub
}

} /* namespace util */
