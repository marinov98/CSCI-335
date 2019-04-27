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
bool is_upper(string s) {
	if (s.empty())
		return false;

	for (const char& c : s) {
		if (!isupper(c))
			return false;
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
	if (s == "GS" || s == "F5")
		is_valid = true;

	// case 2: Numbers 1 through 7
	if (valid_num(s))
		is_valid = true;

	// case 3: Letters A - Z
	if (is_upper(s))
		is_valid = true;

	return is_valid;
}

string str_from_routeset(route_set s) {}

int routesstring2int(string s) {}

string int2route_id(int k) {}

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
