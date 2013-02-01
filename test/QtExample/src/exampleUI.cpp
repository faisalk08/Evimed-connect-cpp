//============================================================================
// Name        : exampleUI.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <QtGui/QApplication>
#include <OauthClientUI.h>
using namespace std;

int main(int argc, char **argv) {

	QApplication app(argc, argv);

	OauthClientUI clientUI;

	clientUI.resize(600,500);
	clientUI.setWindowTitle("Application UI with static library");
	clientUI.show();


	return app.exec();
}
