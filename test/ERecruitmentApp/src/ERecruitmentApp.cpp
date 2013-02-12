//============================================================================
// Name        : ERecruitmentApp.cpp
// Author      : Indra Rusmita
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <QtGui/QApplication>
#include <ERecruitmentView.h>
using namespace std;

int main(int argc, char **argv) {
	string appName = "Erecruitment viewer";
	cout << appName << endl;
	//Q_INIT_RESOURCE(ERecruitment);

	QApplication app(argc, argv);

	ERecruitmentView eRecruitmentView;
	eRecruitmentView.setWindowTitle(appName.c_str());
	eRecruitmentView.show();


	return app.exec();
}
