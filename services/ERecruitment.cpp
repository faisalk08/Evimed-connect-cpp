/*
 * ERecruitment.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: indra
 */

#include "header/ERecruitment.h"

namespace services {

ERecruitment::ERecruitment(string eConfig) {

	//Read config files
	ptree evimedConfig;
	read_ini(eConfig, evimedConfig);

	trialsearch_url = evimedConfig.get<string>("evimed.api_trialsearch_url");
	trialrecruitment_url = evimedConfig.get<string>("evimed.api_trialrecruitment_url");
	trialrecruitment_match_url = evimedConfig.get<string>("evimed.api_trialrecruitment_match_url");
	trialrecruitment_status_url = evimedConfig.get<string>("evimed.api_trialrecruitment_status_url");
}

string ERecruitment::searchTrial(int patientId, int start, int end, string trialParameters){
	string url;
	stringstream id, s, e;
	id << patientId; s << start; e << end;

	url = serverUrl + trialsearch_url + slash + id.str() + questionMark + "start=" + s.str() + ampersand + "end=" + e.str() + ampersand + "trialParameters=" + trialParameters;
	string response = oauthClient->getData(url);

	return response;

}

string ERecruitment::postTrialRecruitment(int patientId, int trialId, string centerCode, string contactAddress, string contactPhone, string comment){
	string url;
	stringstream id, tId;
	id << patientId; tId << trialId;

	url = serverUrl + trialrecruitment_url;
	string query = questionMark + "website=pm";
	url+=query;
//			string data = "patientId=" + id.str() + ampersand + "trialId=" + tId.str() + ampersand + "emailAddress=" + ampersand + "trialCenterCode=";

	ptree jsonData;
	jsonData.put("patientId", patientId);
	jsonData.put("trialId", trialId);
	jsonData.put("contactEmail", emailAddress);
	jsonData.put("trialCenterCode", centerCode);
	jsonData.put("comments", comment);
	jsonData.put("contactPhone", contactPhone);
	jsonData.put("contactAddress", contactAddress);
	stringstream ss;
	write_json(ss, jsonData);

	string response = oauthClient->postData(url, ss.str());

	return response;
}

string ERecruitment::getTrialRecruitment(int patientId, int trialId){
	string url;
	stringstream id, tId;
	id << patientId; tId << trialId;

	url = serverUrl + trialrecruitment_match_url;
	string query = questionMark + "patientId=" + id.str() + ampersand + "trialId=" + tId.str() + ampersand + "website=pm";

	url+= query;

	string response = oauthClient->getData(url);

	return response;
}

string ERecruitment::getTrialRecruitmentStatus(int patientId){
	string url;
	stringstream id, tId;
	id << patientId;

	url = serverUrl + trialrecruitment_status_url;
	string query = questionMark + "patientId=" + id.str() + ampersand + "website=pm";

	url+= query;

	string response = oauthClient->getData(url);

	return response;
}

string ERecruitment::getTrialRecruitmentWithId(int recruitmentId){
	string url;
	stringstream id, tId;
	id << recruitmentId;

	url = serverUrl + trialrecruitment_url;
	string query = slash + id.str() + questionMark + "website=pm";

	url+= query;

	string response = oauthClient->getData(url);

	return response;
}

ERecruitment::~ERecruitment() {
	// TODO Auto-generated destructor stub
}

} /* namespace services */
