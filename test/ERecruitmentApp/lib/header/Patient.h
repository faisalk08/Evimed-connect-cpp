/*
 * Patient.h
 *
 *  Created on: Feb 11, 2013
 *      Author: indra
 */

#ifndef PATIENT_H_
#define PATIENT_H_
#include <iostream.h>
#include <boost/property_tree/ini_parser.hpp>

using namespace std;
using namespace com::evimed::portal;
using namespace boost::property_tree;

namespace services {

class Patient {
public:
	Patient(string evimedConfig);
	string getPatient(int patientId=0, int start=0, int end=10);
	virtual ~Patient();

private :
	string patient_url;
};

} /* namespace services */
#endif /* PATIENT_H_ */
