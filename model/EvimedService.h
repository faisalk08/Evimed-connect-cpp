/*
 * EvimedService.h
 *
 *  Created on: Feb 13, 2013
 *      Author: indra
 */

#ifndef EVIMEDSERVICE_H_
#define EVIMEDSERVICE_H_
#include <iostream>
#include <map>
#include <list>
#include <iterator>
#include <EvimedModel.h>
#include <EvimedConfig.h>
#include <EvimedConnect.h>
#include <EvimedSearchModel.h>
#include <../header/OAuthClient.h>
using namespace std;
using namespace oauth;
using namespace com::evimed::portal;

namespace model {

class EvimedService  {
public:
	EvimedService();
	EvimedService(string api);
	EvimedService(OAuthClient client, EvimedConfig config);
	list<EvimedModel> search(map<string, string> search, bool list);
	EvimedSearchModel search(map<string, string> search);
	EvimedModel details(string id);

	void update(EvimedModel model);
	virtual ~EvimedService();
protected:
	EvimedConfig evimedConfig;
	OAuthClient* aouthClient;
	string api;

	string mapToString(map<string, string> mapData);
};

} /* namespace model */
#endif /* EVIMEDSERVICE_H_ */
