/*
 * OauthClient.cpp
 *
 *  Created on: Dec 27, 2012
 *      Author: indra
 */
#include <OauthClientUI.h>

OauthClientUI::OauthClientUI(QWidget *parent): QWidget (parent){
	bSend = true;
	bAuthorize = true;
	bDeauthorize = false;
	bRequest = true;
	bAccess = false;

	server_url = "http://localhost:9090";
	request_token_url = "/oauth/request_token";
	access_token_url = "/oauth/access_token";
	authorize_url = "/oauth/authorize";
	service_url = "/services/oauth/rest/patient";
	logout_url = "/oauth/logout";
	username = "demo@evimed.com";
	password = "Siedle9A";

	QVBoxLayout *boxLayout = new QVBoxLayout(this);
	boxLayout->setSpacing(2);

	label = new QLabel("Application restful services in C++", this);

	QLabel* serverLabel = new QLabel("Server", this);
	serverText = new QLineEdit();
	serverText->setText(server_url.c_str());

	authorizeButton = new QPushButton("request", this);
	authorizeButton->setGeometry(50, 40, 75, 30);

	QLabel* urlLabel = new QLabel("Url", this);
	urlText = new QLineEdit();
	urlText->setText(server_url.append(service_url).c_str());
	urlText->setEnabled(true);

	sendButton = new QPushButton("send", this);
	sendButton->setGeometry(50, 40, 75, 30);
	sendButton->setEnabled(true);

	QLabel* resultLabel = new QLabel("Result", this);
//	resultText = new QLineEdit();
//
//	responseText = new QTextEdit(this);

	webView = new QWebView(this);

	statusLabel = new QLabel("Status: none", this);

	boxLayout->addWidget(label);
	boxLayout->addWidget(serverLabel);
	boxLayout->addWidget(serverText);
	boxLayout->addWidget(authorizeButton);
	boxLayout->addWidget(urlLabel);
	boxLayout->addWidget(urlText);
	boxLayout->addWidget(sendButton);
	boxLayout->addWidget(resultLabel);
//	boxLayout->addWidget(resultText);
//	boxLayout->addWidget(responseText);
	boxLayout->addWidget(webView);
	boxLayout->addWidget(statusLabel);

	connect(sendButton, SIGNAL(clicked()), this, SLOT(send()));
	connect(authorizeButton, SIGNAL(clicked()), this, SLOT(authorize()));

	setLayout(boxLayout);

}

void OauthClientUI::authorize(){
	string evimedConfig = "/Users/indra/Documents/workspace_indigo/c++_project/exampleUI/exampleUI.app/Contents/MacOS/config/evimed.config";
	string userConfig = "/Users/indra/Documents/workspace_indigo/c++_project/exampleUI/exampleUI.app/Contents/MacOS/config/user.properties";

	if(bRequest){

		if(oauthClient)
			oauthClient =  new com::evimed::portal::EvimedConnect::OAuthClient(serverText->text().toStdString(), evimedConfig, userConfig);
		else
			oauthClient->serverUrl = serverText->text().toStdString();

		string response = oauthClient->request();

		bRequest = false;
		bAccess = true;

		authorizeButton->setText("access");

//		system(url.insert(0, "open ").c_str());
		webView->load(QUrl(response.c_str()));
		webView->show();
//		responseText->setText(url.insert(0, "Please go to the browser and login with this URL").c_str());

	}else

	if(bAccess){
		string response = oauthClient->access();
		bAccess = false;

		authorizeButton->setText("deauthorize...");
		bAuthorize = false;
		sendButton->setEnabled(true);
		urlText->setEnabled(true);
		serverText->setEnabled(false);

		bDeauthorize = true;
		webView->setHtml(response.insert(0,"The client is login! you can now access the server by the used of the text box url and send button, or deauthorize button to logout ").c_str());
	}else

	if(bDeauthorize){
		bAuthorize = true;

		authorizeButton->setText("authorize");
		string response = oauthClient->logout();

		bDeauthorize = false;
		bRequest = true;
		bAccess = false;

		sendButton->setEnabled(false);
		urlText->setEnabled(false);
		serverText->setEnabled(true);

		webView->setHtml(response.c_str());
	}

}

void OauthClientUI::send(){
	cout << "Application restful services in C++" << endl; // prints !!!Hello World!!!

	label->setText("Application restful services in C++");

	string response = oauthClient->getData(urlText->text().toStdString());

	webView->setHtml(response.c_str());
//	responseText->setText(response.c_str());

}


