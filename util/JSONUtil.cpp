/*
 * JSONUtil.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: indra
 */

#include "../header/JSONUtil.h"

namespace util {


string JSONUtil::readJsonValue(string jsonData, string key){
	ptree jsonResponse;
	stringstream s(jsonData);
	read_json(s, jsonResponse);

	string value = jsonResponse.get<string>(key);

	return value;
}

string JSONUtil::getJSONValue(string data, string key){

	return readJsonValue(data, key);
}

list<string> JSONUtil::getJSONArrayValue(string data, string arrayName, string key){
	stringstream s(data);
	ptree JsonResponse;
	read_json(s, JsonResponse);

	list<string> listValue;
	BOOST_FOREACH(ptree::value_type &child, JsonResponse.get_child(arrayName)){
//				cout << child.second.empty() << endl;
		if(child.first.empty())
			listValue.push_front(child.second.get<string>(key));
		else
			listValue.push_front(child.second.data());
	}

	return listValue;
}

string JSONUtil::getJSONString(string data, string key){
	stringstream s(data);
	ptree JsonResponse;
	read_json(s, JsonResponse);

	stringstream ss;
	//ptree jsonResult;

	//getChild(JsonResponse.get_child(key));

//			BOOST_FOREACH(ptree::value_type &child, JsonResponse.get_child(key)){
//
//				//jsonResult.put<ptree::value_type>(key, child.);
////				BOOST_FOREACH(ptree::value_type &secondChild, child.second){
////					cout << secondChild.first.data() + secondChild.second.data() << endl;
////
////					//if(secondChild.second.empty())
////				}
//			}
	//ss << child.second.get("departments") ;
	write_json(ss, JsonResponse.get_child(key));

	return ss.str();
}

/*string getChild(ptree::value_type child, string key){
	BOOST_FOREACH(ptree::value_type &child, child){
		BOOST_FOREACH(ptree::value_type &secondChild, child.second){
			cout << secondChild.first.data() + secondChild.second.data() << endl;
			if(secondChild.second.empty())
				getJSONString(secondChild.second)
		}
	}

	return
}*/

 list<map<string, string> > JSONUtil::getJSONArrayPair(string data, string arrayName){
	stringstream s(data);
	ptree JsonResponse;
	read_json(s, JsonResponse);

	list<map<string, string> > listValue;

	BOOST_FOREACH(ptree::value_type &child, JsonResponse.get_child(arrayName)){
		map<string, string> mapKeyValue;
		BOOST_FOREACH(ptree::value_type &secondChild, child.second){
			string f(secondChild.first.data());
			string s(secondChild.second.data());

			mapKeyValue.insert(pair<string, string>(f, s));
		}
		listValue.push_front(mapKeyValue);

	}

	return listValue;
}

list<map<string, string> > JSONUtil::getJSONArrayPair(string data){
 	stringstream s(data);
 	ptree JsonResponse;
 	read_json(s, JsonResponse);

 	list<map<string, string> > listValue;

 	BOOST_FOREACH(ptree::value_type &child, JsonResponse){
 		map<string, string> mapKeyValue;
 		BOOST_FOREACH(ptree::value_type &secondChild, child.second){
 			string f(secondChild.first.data());
 			string s(secondChild.second.data());

 			mapKeyValue.insert(pair<string, string>(f, s));
 		}
 		listValue.push_front(mapKeyValue);

 	}

 	return listValue;
 }

map<string, string> JSONUtil::getJSONPair(string data){
 	stringstream s(data);
 	ptree JsonResponse;
 	read_json(s, JsonResponse);

 	map<string, string> mapKeyValue;
 	BOOST_FOREACH(ptree::value_type &child, JsonResponse){

 		string f(child.first.data());
 		string s(child.second.data());

 		mapKeyValue.insert(pair<string, string>(f, s));

 	}

 	return mapKeyValue;
 }

map<string, string> JSONUtil::getJSONPair(string data, string arrayName){
	stringstream s(data);
	ptree JsonResponse;
	read_json(s, JsonResponse);

	map<string, string> mapKeyValue;
	BOOST_FOREACH(ptree::value_type &child, JsonResponse.get_child(arrayName)){

		string f(child.first.data());
		string s(child.second.data());

		mapKeyValue.insert(pair<string, string>(f, s));

	}

	return mapKeyValue;
}

/*void JSONUtil::loopArrayData(string data, list<EvimedModel>* listModel, string arrayName){
	list<map<string, string> > listResult;
	if(arrayName=="")
		listResult = getJSONArrayPair(data);
	else
		listResult = getJSONArrayPair(data, arrayName);

	for (list<map<string, string> >::iterator it = listResult.begin(); it != listResult.end(); ++it) {
		listModel->push_front(EvimedModel(*it));
	}
}*/

string JSONUtil::createJSONString(map<string, string> data){
	string lineFeed = "\n";
	ptree jsonString;

	for (map<string, string>::iterator it = data.begin();  it!= data.end(); ++it) {
		jsonString.put(it->first, it->second);
	}

	stringstream ss;
	write_json(ss, jsonString, false);

	const char *s = ss.str().c_str();
	string temp(s);
	//ss.str().copy(temp, s, ss.str().length());
	//s[strcspn(s,"\n")] ='\0';
	//cout << s << endl;
//	char* ptr;
//	if( (ptr = strchr(ss.str().c_str(), '\n')) != NULL)
//	    *ptr = '\0';
//	while(*s && *s != '\n' && *s != '\r') s++;
//	*s=0;
	unsigned int pos = temp.find(lineFeed);
	temp.replace(pos, lineFeed.length(), "asasdas");
	while(pos!=string::npos){
		pos++;
		pos = temp.find(lineFeed, pos);
		temp.replace(pos, lineFeed.length(), "asasdas");
	}

	cout << ss.str() << endl;
	cout << temp << endl;

	return ss.str();
}

} /* namespace util */
