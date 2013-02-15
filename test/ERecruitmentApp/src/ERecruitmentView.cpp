/*
 * ERecruitmentView.cpp
 *
 *  Created on: Feb 6, 2013
 *      Author: indra Rusmita
 */

#include "ERecruitmentView.h"
static string loginHtml =
		"<html>"
		"<body>"
		"<h3>Please Login first!</h3>"
		"</bod>"
		"</html>";

static string resourceFolder = "/ERecruitmentApp.app/Contents/Resources";
static string serverAddress = "http://www.evimed.com";
static string eRecruitmentAddress = "http://www.evimed.com/erecruitment/";
static string profileAddress = "/services/oauth/rest/profile";

ERecruitmentView::ERecruitmentView(QWidget *widget) : QWidget (widget){

	homePath = QDir::currentPath().toStdString() + resourceFolder;
	bLogin = false;
	cout << QDir::currentPath().toStdString() << endl;
	QWidget* gui = loadGui(homePath + "/gui/eRecruitment.ui");

	resize(gui->width(),gui->height());

	QGroupBox *grpLogin = qFindChild<QGroupBox *>(this, "grpLogin");
	QGroupBox *grpPatientList = qFindChild<QGroupBox *>(this, "grpPatientList");
	QGroupBox *grpPatientDetails = qFindChild<QGroupBox *>(this, "grpPatientDetails");
	QGroupBox *grpPatientWidget = qFindChild<QGroupBox *>(this, "grpPatientWidget");
	QGroupBox *grpStatus = qFindChild<QGroupBox *>(this, "grpStatus");

	lblEmailAddress = qFindChild<QLabel*>(this, "lblEmailAddress");
	lblEmailAddress->setText("");

	lblCenterName = qFindChild<QLabel*>(this, "lblCenterName");
	lblCenterName->setText("");

	lblDepartmentName = qFindChild<QLabel*>(this, "lblDepartmentName");
	lblDepartmentName->setText("");

	lblStatus = qFindChild<QLabel*>(this, "lblStatus");
	lblStatus->setText("");

	btnLogin = qFindChild<QPushButton*>(this, "btnLogin");
	//btnLogin->setStyleSheet("background-color:#5bb75b;");
	connect(btnLogin, SIGNAL(clicked()),  this, SLOT(login()));

	cmbPatientList = qFindChild<QComboBox*>(this, "cmbPatientList");
	connect(cmbPatientList, SIGNAL(currentIndexChanged(int)),  this, SLOT(displayDetail(int)));

	wvPatient = qFindChild<QWebView*>(this, "wvPatient");
	wvPatient->setHtml(loginHtml.c_str());
	connect(wvPatient, SIGNAL(loadFinished(bool)),  this, SLOT(loadFinished()));

	tblPatientDetails = qFindChild<QTableWidget*>(this, "tblPatientDetails");
	QStringList valueList;
	tblPatientDetails->setColumnCount(1);
//	tblPatientDetails->setRowCount(1);
	valueList << "Patient Data";
	tblPatientDetails->setHorizontalHeaderLabels(valueList);
//	QStringList keyList;
//	keyList << "Key";
//	tblPatientDetails->setVerticalHeaderLabels(keyList);
//	connect(tblPatientDetails, SIGNAL(cellClicked(int, int)),  this, SLOT(displayDetail(int, int)));

	QMetaObject::connectSlotsByName(this);
	QWebSettings::globalSettings()->enablePersistentStorage("cache");

	QVBoxLayout *mainLayout = new QVBoxLayout();
	QVBoxLayout *leftLayout = new QVBoxLayout();
	QVBoxLayout *rightLayout = new QVBoxLayout();
	QHBoxLayout *hLayout = new QHBoxLayout();

	QHBoxLayout *hLayoutWiget = new QHBoxLayout();
	hLayoutWiget->addWidget(wvPatient);

	grpPatientWidget->setLayout(hLayoutWiget);
	rightLayout->addWidget(grpPatientWidget);

	QVBoxLayout *vLayoutLogin = new QVBoxLayout();

	vLayoutLogin->addWidget(lblEmailAddress);
	vLayoutLogin->addWidget(lblCenterName);
	vLayoutLogin->addWidget(lblDepartmentName);
	vLayoutLogin->addWidget(btnLogin);
	grpLogin->setLayout(vLayoutLogin);
	leftLayout->addWidget(grpLogin);

	QHBoxLayout *hLayoutPatientList = new QHBoxLayout();
	hLayoutPatientList->addWidget(cmbPatientList);
	grpPatientList->setLayout(hLayoutPatientList);
	leftLayout->addWidget(grpPatientList);

	QHBoxLayout *hLayoutPatientDetails = new QHBoxLayout();
	hLayoutPatientDetails->addWidget(tblPatientDetails);
	grpPatientDetails->setLayout(hLayoutPatientDetails);
	leftLayout->addWidget(grpPatientDetails);

	QHBoxLayout *hLayoutStatus = new QHBoxLayout();
	hLayoutStatus->addWidget(lblStatus);
	grpStatus->setLayout(hLayoutStatus);

	hLayout->addLayout(leftLayout);
	hLayout->addLayout(rightLayout);

	mainLayout->addLayout(hLayout);
	mainLayout->addWidget(grpStatus);

	setLayout(mainLayout);

	loadClient();
}

QWidget* ERecruitmentView::loadGui(string ui){
	QUiLoader loader;

	QFile file(ui.c_str());
	file.open(QFile::ReadOnly);

	QWidget *form = loader.load(&file, this);
	file.close();

	return form;
}

void ERecruitmentView::loadClient(){

	string evimedConfig = homePath + "/config/evimed.config";
	string userConfig = homePath + "/config/user.properties";
	//client = OAuthClient(serverAddress, evimedConfig, userConfig);
	EvimedConnect* evimedConnectFactory = EvimedConnect::getInstance();
	evimedConnectFactory->init("user", evimedConfig, userConfig);
	client = evimedConnectFactory->getOAuthClient();
	if(client->isAuthenticated()){
		viewLogin();
	}
}

void ERecruitmentView::viewLogin(){
	displayWebsite(eRecruitmentAddress);
	loadPatientList();
	//lblEmailAddress->setText()
	btnLogin->setText("Logout");
	//btnLogin->setStyleSheet("background-color:red;");
	bLogin = true;
}

void ERecruitmentView::viewLogoff(){
	lblEmailAddress->setText("");
	lblCenterName->setText("");
	lblDepartmentName->setText("");
	//displayWebsite(eRecruitmentAddress);
	wvPatient->setHtml(loginHtml.c_str());
	cmbPatientList->clear();

	btnLogin->setText("Login");
	//btnLogin->setStyleSheet("background-color:#5bb75b;");
	bLogin = false;
}

void ERecruitmentView::displayWebsite(string address){
	string signedUrl;
	signedUrl = client->getSignedUrl(address, false);
	cout << "hello " + signedUrl<< endl;
	wvPatient->load(QUrl(signedUrl.c_str()));
	wvPatient->show();
}

void ERecruitmentView::authenticate(){
	string response;
	cout << "You are not login, please login first!" << endl;
	response = client->request();

	wvPatient->load(QUrl(response.c_str()));
	wvPatient->show();

}

void ERecruitmentView::loadFinished(){
	string authorizeText = "You have successfully authorized 'HTML5 Test Consumer'";
	string accessText = "The client is login!";
	string response;

	if(wvPatient->page()->findText(authorizeText.c_str())){
		response = client->access();
		cout << "accessing " << endl;
		//if(response.find(accessText)!=string::npos){
		if(client->isAuthenticated()){
			viewLogin();
		}

	}

}

void ERecruitmentView::loadPatientList(){
	string response;
	//list<map<string, string> > result;

	//response = client->getData(serverAddress + profileAddress);

//	EvimedService* profileService = new EvimedService(serverAddress + profileAddress);
	map<string, string> param;
//	param.insert(pair<string, string>("website","pm"));
//	list<EvimedModel> profiles = profileService->search(param, false);
//	string emailAddress = profiles.begin()->get("emailAddress");
//	cout << "done " << endl;

	//string emailAddress = client->getJSONValue(response, "emailAddress");
//	lblEmailAddress->setText(emailAddress.c_str());
//	string cm = client->getJSONArrayValue(response, "centers", "name").front();
//	lblCenterName->setText(cm.c_str());
//	string center = client->getJSONString(response, "centers");
//	string dm = client->getJSONArrayValue(center, "departments", "name").front();
//	lblDepartmentName->setText(dm.c_str());

	//response = client->getPatient();
	//result = client->getJSONArrayPair(response, "result");

	string patientUrl = "/services/oauth/rest/patient";
	EvimedService* patientService = new EvimedService(serverAddress + patientUrl);

	param.clear();
	param.insert(pair<string, string>("website","pm"));
	param.insert(pair<string, string>("start","0"));
	param.insert(pair<string, string>("end","10"));
	EvimedSearchModel searchResult = patientService->search(param);
	list<EvimedModel> result = searchResult.getResults();

	map<string, string> mapResult;
	QMap<QString, QVariant> mapAll;

	//for (list<map<string, string> >::iterator var = result.begin(); var != result.end(); ++var) {
	for (list<EvimedModel >::iterator patient = result.begin(); patient != result.end(); ++patient) {

		mapResult = patient->getMap();
		QMap<QString, QVariant> mapVariant;
		for (map<string, string>::iterator it = mapResult.begin(); it != mapResult.end(); ++it) {
			mapVariant.insert(QString(it->first.c_str()), QVariant(it->second.c_str()));//{key, value} e.g. {patientCode:'test', patientId:0}
		}

		//URL
		string patientId = mapVariant.find("patientId").value().toString().toStdString();
		string url = eRecruitmentAddress + "?patientId=" + patientId;
		mapVariant.insert("URL", url.c_str());

		//cmbPatientList->addItem(mapResult.find("patientCode")->second.c_str(), QVariant(mapVariant));//{PatientCode, {key, value}}
		cmbPatientList->addItem(patient->get("patientCode").c_str(), QVariant(mapVariant));//{PatientCode, {key, value}}

		mapAll.insert(mapResult.find("patientCode")->second.c_str(), mapResult.find("patientId")->second.c_str());

	}

	string url = eRecruitmentAddress;
	mapAll.insert("URL", url.c_str());
	cmbPatientList->insertItem(0, "All", QVariant(mapAll));
	cmbPatientList->setCurrentIndex(0);
}

void ERecruitmentView::displayDetail(int index){
	string signedUrl;
	cout << "display Detail" << endl;

	//string response = client->getPatient(cmbPatientList->itemText(index).toInt());
	//cmbPatientList->itemText(index).toStdString()
	QVariant var = cmbPatientList->itemData(index);
	QMap<QString, QVariant> mapVariant = var.toMap();

	string url = mapVariant.find("URL").value().toString().toStdString();
	cout << mapVariant.find("URL").value().toString().toStdString() << endl;
	displayWebsite(url);
	lblStatus->setText(url.c_str());

	tblPatientDetails->setRowCount(mapVariant.size()-1);//minus ignore fields

	int row = 0;
	for (QMap<QString, QVariant>::iterator it = mapVariant.begin(); it!= mapVariant.end(); ++it) {

		if(it.key().startsWith("URL") ||
				it.key().startsWith("departmentId") || it.key().startsWith("centerId") ||
				it.key().startsWith("centerUuid") || it.key().startsWith("patientInfo")
				) continue;


		QTableWidgetItem *keyItem = new QTableWidgetItem(it.key());
		QTableWidgetItem *valueItem = new QTableWidgetItem(it.value().toString());
		tblPatientDetails->setVerticalHeaderItem(row, keyItem);
		tblPatientDetails->setItem(row, 0, valueItem);
		//cout << it.key().toStdString() + " " + it.value().toString().toStdString() << endl;
		row++;

	}
	tblPatientDetails->setRowCount(row);

}

void ERecruitmentView::login(){

	if(!bLogin){

		btnLogin->setText("Please finish the login...");

		if(!client->isAuthenticated()){
			authenticate();
		}

	}else{
		client->logout();

		viewLogoff();
	}

}

ERecruitmentView::~ERecruitmentView() {
	// TODO Auto-generated destructor stub
}

