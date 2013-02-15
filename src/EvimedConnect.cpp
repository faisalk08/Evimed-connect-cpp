/*
 * evimedConnect.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: indra
 */

#include "../header/EvimedConnect.h"

namespace com {

namespace evimed {

namespace portal {

static EvimedConnect* evimedConnect=NULL;
OAuthClient* oauthClient = NULL;

EvimedConnect::EvimedConnect() {
}

EvimedConnect* EvimedConnect::getInstance(){
	if (evimedConnect) return evimedConnect;

	evimedConnect = new EvimedConnect();

	return evimedConnect;
}

EvimedConnect* EvimedConnect::init(string userKey, string evimedConfig, string userConfig){

	this->eConfig = evimedConfig;
	this->uConfig = userConfig;
	this->evimedConfig = new EvimedConfig(evimedConfig, true);
	this->userConfig = new EvimedConfig(userConfig, true);

	return evimedConnect;
}

void EvimedConnect::setUserKey(string userKey){
	this->userKey = userKey;
}

void EvimedConnect::setUserConfig(map<string, string> userMap){
	this->userMap = userMap;
}

OAuthClient* EvimedConnect::getOAuthClient(){
	if(oauthClient) return oauthClient;

	cout << "OATU" << endl;

	oauthClient = new OAuthClient(this->eConfig, this->uConfig);

	return oauthClient;
}

EvimedConfig* EvimedConnect::getEvimedConfig(){
	return this->evimedConfig;
}

EvimedConfig* EvimedConnect::getUserConfig(){
	return this->userConfig;
}

}
}
}

