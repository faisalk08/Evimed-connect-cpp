/*
 * Patient.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: indra
 */

#include "header/Patient.h"

namespace services {

Patient::Patient(){

}
Patient::Patient(string eConfig) {
	string modelname  = "";
	//Read config files
	ptree evimedConfig;
	read_ini(eConfig, evimedConfig);
	patient_url = evimedConfig.get<string>("evimed."+modelname+".url");
}

string Patient::getPatient(int patientId, int start, int end){
	string url;
	stringstream id, s, e;
	id << patientId; s << start; e << end;
	if(patientId==0)
		url = serverUrl + patient_url + questionMark + "start=" + s.str() + ampersand + "end=" + e.str();
	else
		url = serverUrl + patient_url + slash + id.str();

	string response = oauthClient->getData(url);

	return response;

}

Patient::~Patient() {
	// TODO Auto-generated destructor stub
}

} /* namespace services */
