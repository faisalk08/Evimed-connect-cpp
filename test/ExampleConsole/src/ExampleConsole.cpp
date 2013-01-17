//============================================================================
// Name        : ExampleConsole.cpp
// Author      : Indra Rusmita
// Version     :
// Copyright   : Evimed GmbH
// Description : Example of console application using Evimed static library
//============================================================================

#include <iostream>
#include <evimedConnect.h>
using namespace std;
using namespace com::evimed::portal::EvimedConnect;

void authenticateMe(OAuthClient &client){
	string response;
	cout << "You are not login, please login first!" << endl;
	response = client.request();

	system(response.insert(0, "open ").c_str());

	int key;
	cout << "Please press any key, once you are login..." << endl;
	cin >> key;
	//			response = client.authorize();

	response = client.access();
}

void display(string data){
	cout << data << endl;
}

int main() {

	cout << "Example console  application using Evimed static library" << endl;
	string serverUrl = "http://staging.evimed.com";
	string evimedConfig = "config/evimed.config";
	string userConfig = "config/user.properties";

	OAuthClient client = OAuthClient(serverUrl, evimedConfig, userConfig);

	string response;

	if(!client.isAuthenticated()){
		authenticateMe(client);
	}

	list<string> result;
	response = client.getPatient();
	result = client.getJSONValue(response, "result", "patientId");
	for_each(result.begin(), result.end(), display);

	response = client.searchTrial(7313, 0, 3);
	result = client.getJSONValue(response, "trials", "trialId");
	for_each(result.begin(), result.end(), display);

	response = client.getTrialRecruitment(7313, 7919);

	result = client.getJSONValue(response, "missingParameters", "shortName");
	for_each(result.begin(), result.end(), display);

	result = client.getJSONValue(response, "trialCenters", "centerCode");
	for_each(result.begin(), result.end(), display);

	result = client.getJSONValue(response, "patient", "patientId");
	for_each(result.begin(), result.end(), display);

	map<string, string> mapResult = client.getJSONPair(response, "patient");

	for (map<string, string>::iterator it = mapResult.begin(); it != mapResult.end(); ++it) {
		cout << it->first << " " << it->second << endl;
	}

//	client.getTrialRecruitmentStatus(7313);

	response = client.getTrialRecruitmentWithId(8);

	response = client.postTrialRecruitment(7318, 3041, "rene");

//	client.logout();

	cout << response << endl;

	return 0;
}
