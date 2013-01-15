/*
 * WebCookie.cpp
 *
 *  Created on: Jan 8, 2013
 *      Author: indra
 */

#include "WebCookie.h"


WebCookie::WebCookie(QObject *parent){
	cout << "LOAD cookies";

	QFile file("cache/cookies.txt");
	file.open(QIODevice::ReadOnly);
	QDataStream data(&file);
	QString host, path;
	QByteArray name, value;
	QString isSession , isHttp, isSecure;

	data >> host >> name >> value >> path >> isSession >> isHttp >> isSecure;

	cout << "Value " + QString(value).toStdString() ;

	bool http;
	isHttp.contains("TRUE")? http = true: http=false;
	bool secure;
	isSecure.contains("TRUE")? secure = true: secure=false;

	QNetworkCookie nc;
	nc.setName(name);
	nc.setValue(value);
	nc.setPath(path);
	nc.setHttpOnly(http);
	nc.setSecure(secure);

	cout << QString(nc.value()).toStdString() << endl;

	QList<QNetworkCookie> list;
	list.append(nc);

	this->cookies.insert(host, list);

	file.close();

}


QList<QNetworkCookie> WebCookie::cookiesForUrl(const QUrl &url) const{

	if(!this->cookies.value(url.host()).isEmpty()){
		cout << "GET My Cookies" << endl;
		return this->cookies.value(url.host());
	}

	cout << "GET DEFAULT Cookies" << endl;
	return QNetworkCookieJar::cookiesForUrl(url);
}

bool WebCookie::storeCookies(QList<QNetworkCookie> cookies, QUrl url){
	QFile file("cache/cookies.txt");
	file.open(QIODevice::WriteOnly);
	QDataStream data(&file);

	foreach(QNetworkCookie cookie, cookies){
		string Bool;
		data << url.host();
		data << cookie.name();
		data << cookie.value();
		data << cookie.path();
		cookie.isSessionCookie()? Bool = "TRUE": Bool="FALSE";
		cout << "Session " + Bool << endl;
		data << Bool.c_str();
		cookie.isHttpOnly()? Bool = "TRUE": Bool="FALSE";
		data << Bool.c_str();
		cookie.isSecure()? Bool = "TRUE": Bool="FALSE";
		data << Bool.c_str();

	}

	file.close();

	return true;
}

bool WebCookie::setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url){

		cout << "ADD current Cookies" << endl;
		bool update;
		QList<QNetworkCookie> cookies = this->cookies.value(url.host());
		this->cookies.remove(url.host());

		foreach(QNetworkCookie newCookie, cookieList){
			update=false;
			if(newCookie.isSessionCookie()){
				int i = 0;
				foreach(QNetworkCookie prevCookie, cookies){

					if(newCookie.name().contains(prevCookie.name())){
						cout << "FOUND same Cookie name " + QString(newCookie.value()).toStdString()<< endl;
						cookies.removeOne(prevCookie);
						cookies.append(newCookie);
						cout << "CHANGE Cookie name to " + QString(prevCookie.value()).toStdString()<< endl;
						update = true;
						break;
					}
					i++;
				}
				if(!update) {
					cout << "APPEND current Cookies" << endl;
					cookies+=newCookie;
				}
			}

		}

		this->cookies.insert(url.host(),cookies);
		foreach(QNetworkCookie cookie, cookies){
			cout << "CURRENT Cookie name " + QString(cookie.value()).toStdString()<< endl;
		}


		storeCookies(cookies, url);

		return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
}


WebCookie::~WebCookie() {
	// TODO Auto-generated destructor stub

}

