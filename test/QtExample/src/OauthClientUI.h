/*
 * OauthClient.h
 *
 *  Created on: Dec 6, 2012
 *      Author: indra
 */

#ifndef OAUTHCLIENTUI_H_
#define OAUTHCLIENTUI_H_

#include <iostream>
using namespace std;

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QTextLine>
#include <QtGui/QLineEdit>
#include <QtGui/QTextEdit>
#include <QtWebKit/QWebView>

#include <evimedConnect.h>

class OauthClientUI: public QWidget {
	Q_OBJECT
public:
	OauthClientUI(QWidget *parent = 0);

public slots:
	void send();
	void authorize();

private:
	QLabel *label;
//	QLineEdit *usernameText;
//	QLineEdit *passwordText;
	QLineEdit *urlText;
//	QLineEdit *resultText;
	QLabel* statusLabel;
	QPushButton *authorizeButton;
	QPushButton *sendButton;
//	QTextEdit *responseText;
	QLineEdit *serverText;
	QWebView *webView;

	string server_url;
	string request_token_url;
	string access_token_url;
	string authorize_url;
	string service_url;
	string username ;
	string password;
	string logout_url;

	com::evimed::portal::EvimedConnect::OAuthClient *oauthClient;
	bool bSend;
	bool bAuthorize;
	bool bDeauthorize;
	bool bRequest;
	bool bAccess;
};


#endif /* OAUTHCLIENTUI_H_ */
