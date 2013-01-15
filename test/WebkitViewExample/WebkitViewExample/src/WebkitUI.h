/*
 * WebkitUI.h
 *
 *  Created on: Jan 3, 2013
 *      Author: indra
 */

#ifndef WEBKITUI_H_
#define WEBKITUI_H_

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLineEdit>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtWebKit/QWebView>
#include <QtWebKit/QWebFrame>
#include <QtNetwork/QNetworkCookieJar>
#include <QtNetwork/QNetworkProxyFactory>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkDiskCache>
#include <QtNetwork/QAbstractNetworkCache>
#include <iostream>
#include <WebCookie.h>

using namespace std;

class WebkitUI : public QWidget{
	Q_OBJECT
public:
	WebkitUI(QWidget *widget = 0);
	virtual ~WebkitUI();
private:
	QWebView *webView;

	QString jQuery;
	QString backboot;
	QString underscore;
	QString require;
	QString evimedJs;
	QFile *cachedFile;
	QNetworkReply *reply;

	QWebFrame *webFrame;

protected slots:
	QString loadScript(string fileName);
	void namFinished(QNetworkReply* reply);
	void replyReadyRead();
	void replyFinished();
};

#endif /* WEBKITUI_H_ */
