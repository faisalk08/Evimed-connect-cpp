/*
 * ERecruitment.h
 *
 *  Created on: Feb 11, 2013
 *      Author: indra
 */

#ifndef ERECRUITMENT_H_
#define ERECRUITMENT_H_
#include <iostream.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
using namespace std;
using namespace com::evimed::portal;
using namespace boost::property_tree;

namespace services {

class ERecruitment {
public:
	ERecruitment();
	ERecruitment(string evimedConfig);
	string getTrialRecruitment(int patientId, int trialId);
	string getTrialRecruitmentStatus(int patientId);
	string getTrialRecruitmentWithId(int recruitmentId);
	string postTrialRecruitment(int patientId, int trialId, string centerCode, string contactAddress="", string contactPhone="", string comment="");
	string searchTrial(int patientId, int start=0, int end=5, string trialParameters="type%3D1");
	virtual ~ERecruitment();

private:
	string trialrecruitment_url;
	string trialrecruitment_match_url;
	string trialrecruitment_status_url;
	string trialsearch_url;
};

} /* namespace services */
#endif /* ERECRUITMENT_H_ */
