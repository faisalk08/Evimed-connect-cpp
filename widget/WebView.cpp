/*
 * WebView.cpp
 *
 *  Created on: Jan 22, 2013
 *      Author: indra
 */

#include "header/WebView.h"

namespace widget {

static string cacheDir = "cache";
static int maxPages = 10;
WebView::WebView() {
	cout << "Init webview" << endl;
	webView = NULL;
	webView = new QWebView();

	WebCookie *cookie = new WebCookie();
	QWebSettings::globalSettings()->enablePersistentStorage(cacheDir.c_str());
	QWebSettings::globalSettings()->setMaximumPagesInCache(maxPages);
	webView->page()->networkAccessManager()->setCookieJar(cookie);
}

QWebView* WebView::getWebView(){
	if(!webView) return 0;
	return webView;
}

WebView::~WebView() {
	// TODO Auto-generated destructor stub
}

}  // namespace widget
