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
#include <../util/EvimedUtil.h>
using namespace std;
using namespace oauth;
using namespace com::evimed::portal;
using namespace util;

namespace model {

class EvimedService  {
public:
	EvimedService();
	EvimedService(string api);
	EvimedService(OAuthClient client, EvimedConfig config);
	EvimedSearchModel add(string data);
	EvimedSearchModel add(EvimedModel data);
	EvimedSearchModel update(map<string, string> search, EvimedModel data);
	EvimedSearchModel remove(EvimedModel data);
	EvimedSearchModel remove(string id);
	list<EvimedModel> search(map<string, string> search, bool list);
	EvimedSearchModel search(map<string, string> search);
	EvimedModel details(string id);
	OAuthClient* getOAuthClient();

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
