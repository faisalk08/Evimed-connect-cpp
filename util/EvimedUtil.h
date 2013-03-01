/*
 * EvimedUtil.h
 *
 *  Created on: Feb 22, 2013
 *      Author: indra
 */

#ifndef EVIMEDUTIL_H_
#define EVIMEDUTIL_H_
#include <iostream>
#include <map>
#include <list>
#include <JSONUtil.h>
#include <EvimedModel.h>

using namespace std;
using namespace model;

namespace util {

class EvimedUtil {
public:
	EvimedUtil();
	static void loopArrayData(string data, list<EvimedModel>* listModel, string arrayName);
	virtual ~EvimedUtil();
};

} /* namespace util */
#endif /* EVIMEDUTIL_H_ */
