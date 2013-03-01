/*
 * PatientService.cpp
 *
 *  Created on: Feb 22, 2013
 *      Author: indra
 */

#include "PatientService.h"

namespace model {

PatientService::PatientService() {
	// TODO Auto-generated constructor stub

}

PatientService::PatientService(string api) : EvimedService(api) {
	// TODO Auto-generated constructor stub

}

EvimedModel PatientService::add(EvimedModel data){
	string searchUrl;
	searchUrl = api;

	string response = getOAuthClient()->postData(searchUrl, data.toString());
	return EvimedModel(JSONUtil::getJSONPair(response));
}

EvimedSearchModel PatientService::remove(EvimedModel data){
	string searchUrl;
	searchUrl = api + "/" + data.get("patientId");
	string response = getOAuthClient()->deleteData(searchUrl);
	return EvimedSearchModel(response);
}

PatientService::~PatientService() {
	// TODO Auto-generated destructor stub
}

} /* namespace model */
