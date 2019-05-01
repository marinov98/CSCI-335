/******************************************************************************
  Title          : subway_route.cpp
  Author         : Marin Pavlinov Marinov
  Created on     : April 22, 2018
  Description    : cpp file for the SubwayRoute object
  Purpose        : implements subway_route
  Usage          :
  Build with     : c++11
  Modifications  :

******************************************************************************/

#include "subway_route.h"

/*******************************************************************************
 *                    Functions related to subway routes                        *
 ******************************************************************************/

bool is_valid_num(string s) {
	return (s[0] >= '1' && s[0] <= '7');
}

bool is_route_id(string s) {
	// if string is empty, no need to do further checks
	if (s.empty())
		return false;

	// convert to upper case if necessary
	for (unsigned int i = 0; i < s.size(); i++)
		if (isalpha(s[i]) && islower(s[i]))
			s[i] = toupper(s[i]);

	// case 1: GS or FS
	if (s == "GS" || s == "FS")
		return true;

	// case 2: Numbers 1 through 7
	if (is_valid_num(s))
		return true;

	// case 3: Letters A - Z
	if (isalpha(s[0]))
		return true;

	// none of the 3 cases are true if program comes here
	return false;
}

string str_from_routeset(route_set s) {
	string route_str("");

	for (int i = 1; i < 36; i++) {
		// get ith bit
		bool bit = (s & (1 << i));
		// check if bit is one or 0
		if (bit == 1) {
			route_str += int2route_id(i);
			// separate routes by  a space
			route_str += " ";
		}
	}

	// remove space at the back
	route_str.pop_back();

	return route_str;
}

int routestring2int(string s) {
	// FS and GS case
	if (s == "GS")
		return 8;

	if (s == "FS")
		return 9;

	// A-Z case
	/*
	    if its an alphabetical letter the ascii value of its uppercase minus 55
	    falls within the range of [0,63]
	    the -55 (Assuming letter is uppercase) makes the values start at 10 and end at 35
	    that is why I use toupper so that lowercase inputs are valid and still yield the same result
	 */
	if (isalpha(s[0]))
		return (static_cast<int>(toupper(s[0]) - 55));

	// 1-7 case
	if (is_valid_num(s))
		return stoi(s);

	// None of the above
	return 0;
}

string int2route_id(int k) {
	// FS and GS case
	if (k == 8)
		return "GS";

	if (k == 9)
		return "FS";

	// A-Z case
	if (k > 9 || k < 36) {
		// utilize c++11 string contructor
		string id(1, static_cast<char>(k + 55));
		return id;
	}

	// 1-7
	if (k > 0 || k < 8)
		return to_string(k);

	// None of the above
	return "";
}

/*******************************************************************************
 *                           SubwayRoute Class                                  *
 ******************************************************************************/

list<int> SubwayRoute::station_list() const {
	return stations;
}

void SubwayRoute::add_station_to_route(int station_id) {
	stations.push_back(station_id);
}

route_set SubwayRoute::get_routeset() const {
	return routes;
}
