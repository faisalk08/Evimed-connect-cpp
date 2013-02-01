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

	server_url = "http://staging.evimed.com";
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
	string evimedConfig = "config/evimed.config";
	string userConfig = "config/user.properties";

	if(bRequest){

		if(!oauthClient)
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
	cout << "Getting the data from the url " << endl; // prints !!!Hello World!!!

	label->setText("Get Data");

	string signedUrl;
	string response = oauthClient->getData(urlText->text().toStdString(), signedUrl);

	//webView->setHtml(response.c_str());
//	responseText->setText(response.c_str());
	QWebSettings::globalSettings()->enablePersistentStorage("cache");
	QWebSettings::globalSettings()->setMaximumPagesInCache(10);
	webView->load(QUrl(signedUrl.c_str()));
	webView->show();
	cout << signedUrl.insert(0, "my URL ").c_str() << endl;
}


