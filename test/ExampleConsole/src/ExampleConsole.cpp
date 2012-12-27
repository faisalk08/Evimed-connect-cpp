//============================================================================
// Name        : ExampleConsole.cpp
// Author      : Indra Rusmita
// Version     :
// Copyright   : Evimed GmbH
// Description : Example console  application using Evimed static library
//============================================================================

#include <iostream>
#include <evimedConnect.h>
using namespace std;

int main() {

	cout << "Example console  application using Evimed static library" << endl;
	string serverUrl = "http://localhost:9090";
	string evimedConfig = "config/evimed.config";
	string userConfig = "config/user.properties";

	com::evimed::portal::EvimedConnect::OAuthClient client = com::evimed::portal::EvimedConnect::OAuthClient(serverUrl, evimedConfig, userConfig);

	string response = client.getData("http://localhost:9090/services/oauth/rest/patient");

	if(response.empty()){
		cout << "You are not login, please login first!" << endl;
		response = client.request();
		system(response.insert(0, "open ").c_str());

		int key;
		cout << "Press any key, once you are login..." << endl;
		cin >> key;

		response = client.access();
		response = client.getData("http://localhost:9090/services/oauth/rest/patient");
	}


	cout << response << endl;

	return 0;
}
