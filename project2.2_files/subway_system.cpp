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
	// make sure we have not passed our limit
	if (this->_array_index < MAX_STATIONS) {
		// check if insertion was successful
		if (!_portals.emplace(make_pair(portal, this->_array_index)).second)
			return 0;
		else {
			// store bit mask into array and increment index
			route_masks[this->_array_index++] = portal.routes();

			return 1;
		}
	}
}

void SubwaySystem::list_all_stations(ostream& out) const {
	out << _names.listall(out);
}

void SubwaySystem::list_all_portals(ostream& out, string station_name) const {
	for (const auto& portal : this->_portals) {
		if (portal.first.get_station_name() == station_name)
			out << portal.first.name();
	}
}

void SubwaySystem::list_stations_of_route(ostream& out, route_id route) const {
	out << route;
}

int SubwaySystem::form_stations() {
	// check if array of portals was created
	if (0 == this->_array_index)
		return 0;

	int sets_created = 0;

	// Union the sets and do stuff down here
}

bool SubwaySystem::get_portal(string name_to_find, SubwayPortal& portal) const {
	for (const auto& portals : this->_portals) {
		if (portals.first.name() == name_to_find) {
			// copy into parameter
			portal = portals.first.name();
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
		double distance = distance_between(portal.first.p_location(), GPS(longitude, latitude));

		// keep track of distance and portal name
		if (distance < min) {
			min = distance;
			closest_portal_name = portal.first.name();
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
		double distance = distance_between(portal.first.p_location(), GPS(longitude, latitude));

		// keep track of min and the routes of the portal
		if (distance < min) {
			min = distance;
			closest_routes = portal.first.routes();
		}

		// if distance is 0, we can automatically confirm that its the closest portal because it is
		// located right on top of the given coordinates
		if (0 == distance)
			return str_from_routeset(closest_routes);
	}

	return str_from_routeset(closest_routes);
}
