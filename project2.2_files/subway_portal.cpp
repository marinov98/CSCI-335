/******************************************************************************
  Title          : subway_portal.cpp
  Author         : Marin Pavlinov Marinov
  Created on     : April 22, 2018
  Description    : Subway Portal header
  Purpose        : implement subway portal
  Usage          :
  Build with     : c++11
  Modifications  :

******************************************************************************/

#include "subway_portal.h"

SubwayPortal::SubwayPortal() {}

string SubwayPortal::create_name(string s) {
	string name = "";
	// do stuff;

	return name;
}

SubwayPortal::SubwayPortal(string data_row) {
	this->_name = create_name(data_row);
}

double SubwayPortal::distance_from(double latitude, double longitude) {
	/*
	 construct GPS object to:
	 i) check if coardinates are valid
	 ii) use haversine function I defined in gps.h
	*/
	GPS location(longitude, latitude);

	return distance_between(this->_location, location);
}

double distance_between(SubwayPortal portal1, SubwayPortal portal2) {
	// distance_between with GPS parameters uses haversine function
	return distance_between(portal1._location, portal2._location);
}

bool same_routes(SubwayPortal portal1, SubwayPortal portal2) {}

bool same_station(SubwayPortal portal1, SubwayPortal portal2) {}

ostream& operator<<(ostream& out, SubwayPortal e) {
	out << "cordinates of portal:\n" << e._location;
}

string SubwayPortal::name() const {
	return this->_name;
}

bool SubwayPortal::can_access(route_set route) const {}

GPS SubwayPortal::p_location() const {
	return this->_location;
}

GPS SubwayPortal::s_location() const {}

route_set SubwayPortal::routes() const {}