/*
 * WebkitUI.cpp
 *
 *  Created on: Jan 3, 2013
 *      Author: indra
 */

#include "WebkitUI.h"

WebkitUI::WebkitUI(QWidget *widget) : QWidget (widget){

	webView = new QWebView(this);
	QWebSettings::globalSettings()->enablePersistentStorage("cache");
	QWebSettings::globalSettings()->setMaximumPagesInCache(10);

	WebCookie *cookie = new WebCookie();
	webView->page()->networkAccessManager()->setCookieJar(cookie);


	 QNetworkAccessManager *manager = webView->page()->networkAccessManager();
	 connect(manager, SIGNAL(finished(QNetworkReply*)),
			 this, SLOT(namFinished(QNetworkReply*)));

	webView->load(QUrl("http://www.evimed.com/erecruitment/"));
	webView->show();

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(webView);

	setLayout(layout);

}


void WebkitUI::namFinished(QNetworkReply* networkReply){
	string cache = "cache/";
	reply = networkReply;
	QUrl url = reply->url();
	QString fileName = QFileInfo(url.path()).fileName();


	if(!fileName.isEmpty()){
//		cout << "Create file " + fileName.toStdString()<< endl;
		if(fileName.right(3)==".js") cache+= "scripts/";
		else if(fileName.right(3)=="png") cache+= "images/";
		else if(fileName.right(3)=="css") cache+= "stylesheets/";


		QDir dir(cache.c_str());
		if(!dir.exists()){
			cout << "Create Directory " + dir.absolutePath().toStdString() << endl;
			QDir d = QDir();
			d.mkpath(cache.c_str());

		}

		cachedFile = new QFile(cache.c_str() + fileName);
		cachedFile->open(QIODevice::WriteOnly);
		connect(reply, SIGNAL(readyRead()), this, SLOT(replyReadyRead()));
		connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));
	}
}

void WebkitUI::replyFinished(){
	cachedFile->flush();
	cachedFile->close();
}
void WebkitUI::replyReadyRead(){
	if(cachedFile){
		cout << "ready read" << endl;
		cachedFile->write(reply->readAll());
	}
	reply->deleteLater();
}


QString WebkitUI::loadScript(string fileName){
	QFile file;
	file.setFileName(fileName.c_str());
	file.open(QIODevice::ReadOnly);
	QString result =  file.readAll();
	file.close();
	return result;
}


WebkitUI::~WebkitUI() {
	// TODO Auto-generated destructor stub
}

