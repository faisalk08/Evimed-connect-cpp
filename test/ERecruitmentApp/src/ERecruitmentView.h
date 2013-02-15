/*
 * ERecruitmentView.h
 *
 *  Created on: Feb 6, 2013
 *      Author: indra Rusmita
 */

#ifndef ERECRUITMENTVIEW_H_
#define ERECRUITMENTVIEW_H_
#include <EvimedConnect.h>
#include <EvimedModel.h>
#include <EvimedService.h>

#include <iostream>

#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QComboBox>
#include <QtGui/QListView>
#include <QtGui/QTableWidget>
#include <QtWebKit/QWebView>
#include <QtUiTools/QtUiTools>
#include <unistd.h>

using namespace std;
//using namespace com::evimed::portal::EvimedConnect;
using namespace com::evimed::portal;
using namespace model;

class ERecruitmentView : public QWidget{
	Q_OBJECT
public:
	ERecruitmentView(QWidget *widget=0);
	virtual ~ERecruitmentView();

private slots:
	void loadFinished();
	void login();
	void displayDetail(int index);
	//void displayDetail(int row, int col);

private:
	QWidget* loadGui(string ui);
	void authenticate();
	void loadClient();
	void loadPatientList();
	void displayWebsite(string address);
	void viewLogin();
	void viewLogoff();

	QPushButton *btnLogin;
	QComboBox *cmbPatientList;
	QWebView *wvPatient;
	QListView *lvPatientDetails;
	QLabel *lblEmailAddress;
	QTableWidget *tblPatientDetails;
	QLabel *lblDepartmentName;
	QLabel *lblCenterName;
	QLabel *lblStatus;

	bool bLogin;
	string homePath;
//	string serverAddress;
//	string eRecruitmentAddress;
	OAuthClient* client;
	EvimedConnect* evimedConnectFactory;

};

#endif /* ERECRUITMENTVIEW_H_ */
