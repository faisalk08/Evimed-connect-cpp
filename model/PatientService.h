/*
 * PatientService.h
 *
 *  Created on: Feb 22, 2013
 *      Author: indra
 */

#ifndef PATIENTSERVICE_H_
#define PATIENTSERVICE_H_
#include <iostream>
#include <EvimedService.h>
using namespace std;

namespace model {

class PatientService : public EvimedService  {
public:
	PatientService();
	PatientService(string api);
	EvimedModel add(EvimedModel data);
	EvimedSearchModel remove(EvimedModel data);
	virtual ~PatientService();
};

} /* namespace model */
#endif /* PATIENTSERVICE_H_ */
