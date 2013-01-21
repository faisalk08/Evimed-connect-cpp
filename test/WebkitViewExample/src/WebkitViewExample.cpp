//============================================================================
// Name        : WebkitViewExample.cpp
// Author      : Indra Rusmita
// Version     :
// Copyright   : Evimed GmbH
// Description : Erecruitment viewer
//============================================================================

#include <iostream>
#include <QtGui/QApplication>
#include <WebkitUI.h>
using namespace std;

int main(int argc, char **argv) {
	string appName = "Erecruitment viewer";
	cout << appName << endl;

	QApplication app(argc, argv);

	WebkitUI webkitUI;
	webkitUI.resize(600,500);
	webkitUI.setWindowTitle(appName.c_str());
	webkitUI.show();


	return app.exec();
}
