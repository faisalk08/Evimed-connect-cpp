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

OAuthClient* EvimedService::getOAuthClient(){
	return this->aouthClient;
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

EvimedSearchModel EvimedService::add(string data){
	string searchUrl;
	searchUrl = api;

	string response = this->aouthClient->postData(searchUrl, data);
	return EvimedSearchModel(response);
}


EvimedSearchModel EvimedService::add(EvimedModel data){
	string searchUrl;
	searchUrl = api;

	string response = this->aouthClient->postData(searchUrl, data.toString());
	return EvimedSearchModel(response);
}


EvimedSearchModel EvimedService::update(map<string, string> search, EvimedModel data){
	string searchUrl;
	searchUrl = mapToString(search);
	searchUrl = api + "/" + data.get("id") + searchUrl;
	string response = this->aouthClient->putData(searchUrl, data.toString());
	return EvimedSearchModel(response);
}

EvimedSearchModel EvimedService::remove(EvimedModel data){
	string searchUrl;
	searchUrl = api + "/" + data.get("id");
	string response = this->aouthClient->deleteData(searchUrl);
	return EvimedSearchModel(response);
}

EvimedSearchModel EvimedService::remove(string id){
	string searchUrl;
	searchUrl = api + "/" + id;
	string response = this->aouthClient->deleteData(searchUrl);
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
	EvimedUtil::loopArrayData(response, &models, "");

	return models;
}

EvimedService::~EvimedService() {
	// TODO Auto-generated destructor stub
}

} /* namespace model */
