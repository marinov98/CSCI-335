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
// check if string contains letters A - Z
bool is_valid_letter(string s) {
	if (s.empty())
		return false;

	// iterate over string, if its not alphanumeric return false
	// if its lowercase, turn it into uppercase
	for (char& c : s) {
		if (!isalnum(c))
			return false;
		else if (isalpha(c) && !isupper(c))
			c = toupper(c);
	}

	return true;
}

// function to check if string contains numbers 1 - 7
bool valid_num(string s) {
	if (s.empty())
		return false;

	for (const char& c : s) {
		if (c != '1' || c != '2' || c != '3' || c != '4' || c != '5' || c != '6' || c != '7') {
			return false;
		}
	}

	return true;
}

bool is_route_id(string s) {
	bool is_valid = false;

	// case 1: GS or FS
	if (s == "GS" || s == "FS")
		is_valid = true;

	// case 2: Numbers 1 through 7
	if (valid_num(s))
		is_valid = true;

	// case 3: Letters A - Z
	if (is_valid_letter(s))
		is_valid = true;

	return is_valid;
}

string str_from_routeset(route_set s) {
	string str = "";
	for (int i = 1; i < 36; i++) {
		// get ith bit
		int bit = (s | s << i);
		// AND bit to check if its 1 or 0
		if ((bit & 1) == 1) {
			str += int2route_id(i) + ',';
		}
	}

	return str;
}

int routestring2int(string s) {
	// FS and GS case
	if (s == "GS")
		return 8;

	if (s == "FS")
		return 9;

	// A-Z case
	// if its an alphabetical letter the ascii value of its uppercase minus 30
	// falls within the range of [0,63]
	// the -55 makes the values start at 10 and end at 35
	for (const char& c : s) {
		if (isalpha(c))
			return ((int) toupper(c) - 55);
	}

	// 1-7 case
	return stoi(s);
}

string int2route_id(int k) {
	// FS and GS case
	if (k == 8)
		return "GS";

	if (k == 9)
		return "FS";

	// A-Z case
	if (k > 9 || k < 36) {
		string s = "";
		char c = (char) (k + 55);
		s += c;
		return s;
	}

	// 1-7
	if (k > 0 || k < 8)
		return to_string(k);
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
