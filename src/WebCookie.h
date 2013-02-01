/*
 * WebCookie.h
 *
 *  Created on: Jan 8, 2013
 *      Author: indra
 */

#ifndef WEBCOOKIE_H_
#define WEBCOOKIE_H_

#include <iostream>
#include <QtNetwork/QNetworkCookieJar>
#include <QtCore/QMap>
#include <QtCore/QDataStream>
#include <QtCore/QFile>
#include <QtCore/QDir>

using namespace std;


class WebCookie : public QNetworkCookieJar{
public:
	WebCookie();
	virtual ~WebCookie();
	QList<QNetworkCookie> cookiesForUrl(const QUrl &url) const;
	bool setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url);
private:
	QMap< QString, QList<QNetworkCookie> > cookies;
	bool storeCookies(QList<QNetworkCookie> cookies, const QUrl url);
	bool checkDir(string path);
};

#endif /* WEBCOOKIE_H_ */
