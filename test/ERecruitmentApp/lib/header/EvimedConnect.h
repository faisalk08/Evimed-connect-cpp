/*
 * evimedconnect.h
 *
 *  Created on: Dec 19, 2012
 *      Author: indra
 */

#ifndef EVIMEDCONNECT_H_
#define EVIMEDCONNECT_H_
/*
#if __GNUC__ >= 4
#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#endif
*/

#include <iostream>
#include <OAuthClient.h>
#include <../model/EvimedConfig.h>

using namespace std;
using namespace boost::property_tree;
using namespace util;
using namespace model;
using namespace oauth;

namespace com {
namespace evimed {
namespace portal {

class EvimedConnect {
public:

	EvimedConnect* init(string userKey="user", string evimedConfig="config/evimed.config", string userConfig="config/user.config");

	static EvimedConnect* getInstance();

	void setUserKey(string userKey="user");
	//void setEvimedConfig(map<string, string> evimedConfig="config/evimed.config");
	void setUserConfig(map<string, string> userConfig);

	OAuthClient* getOAuthClient();

	EvimedConfig* getEvimedConfig();
	EvimedConfig* getUserConfig();

	ptree pevimedConfig;
	ptree puserConfig;

private:
	EvimedConnect();
	OAuthClient* getOAuthClient(string evimedConfig, string userConfig);
	EvimedConfig* evimedConfig;
	EvimedConfig* userConfig;
	map<string, string> userMap;
	string userKey;

	string eConfig;
	string uConfig;

}; // namespace Evimedwrapper

} // namespace portal

} // namespace evimed

} // namespace com

#endif /* EVIMEDCONNECT_H_ */

