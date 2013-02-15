/*
 * WebView.h
 *
 *  Created on: Jan 22, 2013
 *      Author: indra
 */

#ifndef WEBVIEW_H_
#define WEBVIEW_H_
#include <iostream>
#include <WebCookie.h>
#include <QtWebKit/QWebView>

using namespace std;

namespace widget {

class WebView {
public:
	WebView();
	QWebView *webView;
	QWebView *getWebView();
	virtual ~WebView();
private:
};

}  // namespace widget

#endif /* WEBVIEW_H_ */
