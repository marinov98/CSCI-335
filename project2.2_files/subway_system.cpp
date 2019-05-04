/******************************************************************************
  Title          : subway_system.cpp
  Author         : Marin Pavlinov Marinov
  Created on     : April 22, 2018
  Description    : Subway System header file
  Purpose        : implement Subway System
  Usage          :
  Build with     : c++11
  Modifications  :

******************************************************************************/

#include "subway_system.h"

int SubwaySystem::add_portal(SubwayPortal portal) {
	bool res = _portals.insert(pair<SubwayPortal, int>(portal, this->_portal_index)).second;

	// insert station name into the hashtable I implemented
	// my hashtable will not insert the name if its already in the set
	this->_names.insert(__ItemType(portal.get_station_name(), 0));

	// check if insertion was successful
	if (!res)
		return 0;
	else {
		this->_portal_index++;
		return 1;
	}
}

void SubwaySystem::list_all_stations(ostream& out) const {
	out << _names.listall(out);
}

void SubwaySystem::list_all_portals(ostream& out, string station_name) const {
	for (const auto& portal : this->_portals) {
		auto curr_portal = portal.first;
		if (curr_portal.get_station_name() == station_name)
			out << curr_portal.get_station_name();
	}
}

void SubwaySystem::list_stations_of_route(ostream& out, route_id route) const {
	out << route;
}

int SubwaySystem::form_stations() {}

bool SubwaySystem::get_portal(string name_to_find, SubwayPortal& portal) const {
	for (const auto& portal : this->_portals) {
		// iterator to store the portal object found in a variable
		auto curr_portal = this->_portals.find(portal);

		// create string to compare with name_to_find
		string name(curr_portal->first.name());

		if (name == name_to_find) {
			// copy into parameter
			portal = curr_portal->first;
			return true;
		}
	}

	return false;
};

string SubwaySystem::nearest_portal(double latitude, double longitude) const {
	double min = numeric_limits<double>::max();
	// string to keep track of which portal ends upbeing the lowest
	string closest_portal_name("");
	for (const auto& portal : this->_portals) {
		auto curr_portal = portal.first;

		GPS curr_portal_location = curr_portal.p_location();
		string curr_portal_name(curr_portal.name());

		double distance = distance_between(curr_portal_location, GPS(longitude, latitude));

		// keep track of distance and portal name
		if (distance < min) {
			min = distance;
			closest_portal_name = curr_portal_name;
		}

		// if distance is 0, we can automatically confirm that its the closest portal because it is
		// located right on top of the given coordinates
		if (0 == distance)
			return closest_portal_name;
	}

	return closest_portal_name;
}

string SubwaySystem::nearest_routes(double latitude, double longitude) const {
	double min = numeric_limits<double>::max();

	route_set closest_routes = 0;

	for (const auto& portal : this->_portals) {
		auto curr_portal = portal.first;

		GPS curr_portal_location = curr_portal.p_location();
		route_set curr_portal_route = curr_portal.routes();

		double distance = distance_between(curr_portal_location, GPS(longitude, latitude));

		// keep track of min and the routes of the portal
		if (distance < min) {
			min = distance;
			closest_routes = curr_portal_route;
		}

		// if distance is 0, we can automatically confirm that its the closest portal because it is
		// located right on top of the given coordinates
		if (0 == distance)
			return str_from_routeset(closest_routes);
	}

	return str_from_routeset(closest_routes);
}
