/*
 * EvimedService.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: indra
 */

#include "EvimedService.h"

namespace model {

EvimedService::EvimedService() {
	// TODO Auto-generated constructor stub
}

EvimedService::EvimedService(string api){
	this->api = api;
	this->aouthClient = EvimedConnect::getInstance()->getOAuthClient();
}

EvimedService::EvimedService(OAuthClient client, EvimedConfig config) {
	// TODO Auto-generated constructor stub

}

EvimedModel EvimedService::details(string id){
	string response = this->aouthClient->getData(api+ "/" + id);
	return EvimedModel(JSONUtil::getJSONPair(response));
}

EvimedSearchModel EvimedService::search(map<string, string> search){
	string searchUrl;
	searchUrl = mapToString(search);
	searchUrl = api + searchUrl;
	string response = this->aouthClient->getData(searchUrl);
	return EvimedSearchModel(response);
}

string EvimedService::mapToString(map<string, string> mapData){
	string params ="?";
	for(map<string, string>::iterator it=mapData.begin(); it!= mapData.end(); ++it){
		cout << it->first << endl;
		cout << it->second << endl;

		string pair(it->first + "=" + it->second);
		params += pair + "&";
	}

	return params = params.substr(0, params.size()-1);
}

list<EvimedModel> EvimedService::search(map<string, string> search, bool isList){
	string searchUrl;
	searchUrl = mapToString(search);
	searchUrl = api + searchUrl;
	string response = this->aouthClient->getData(searchUrl);

	list<EvimedModel> models;
	JSONUtil::loopArrayData(response, &models, "");

	return models;
}

EvimedService::~EvimedService() {
	// TODO Auto-generated destructor stub
}

} /* namespace model */
