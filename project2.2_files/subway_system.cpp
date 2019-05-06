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
	if (this->p_array_index < MAX_STATIONS) {
		if (-1 == this->_p_names.insert(__ItemType(portal.name(), this->p_array_index)))
			return 0;
		else {
			// store in array of parent trees
			this->_parents[this->p_array_index] = portal;
			this->route_masks[this->p_array_index] = portal.routes();
			this->p_array_index++;
			return 1;
		}
	}

	return 0;
}

void SubwaySystem::list_all_stations(ostream& out) const {
	out << _s_names.listall(out);
}

void SubwaySystem::list_all_portals(ostream& out, string station_name) const {
	for (unsigned int i = 0; i < MAX_STATIONS; i++) {
		if (this->_parents[i].get_station_name() == station_name)
			out << this->_parents[i].name();
	}
}

void SubwaySystem::list_stations_of_route(ostream& out, route_id route) const {
	// probably wrong to be fixed later
	out << route;
}

int SubwaySystem::form_stations() {
	// check if array of portals was created
	// if p_array index is still 0, that means nothing was inserted yet
	if (0 == this->p_array_index)
		return 0;

	int sets_created = 0;

	// Union the sets and do stuff down here
}

bool SubwaySystem::get_portal(string name_to_find, SubwayPortal& portal) const {
	// if its not found, we cannot get the name
	// Since I modified find in my hash table to return the position instead of just
	// 1 , I can now use it find the portal in the parent trees array
	int res = this->_p_names.find(__ItemType(name_to_find, 0));

	if (-1 == res)
		return false;

	// copy data into parameter
	portal = this->_parents[res];
	return true;
};

string SubwaySystem::nearest_portal(double latitude, double longitude) const {
	double min = numeric_limits<double>::max();

	string closest_portal("");
	double distance;

	for (unsigned int i = 0; i < MAX_STATIONS; i++) {
		distance = distance_between(this->_parents[i].p_location(), GPS(longitude, latitude));

		if (distance < min) {
			min = distance;
			closest_portal = this->_parents[i].name();
		}
	}

	return closest_portal;
}

string SubwaySystem::nearest_routes(double latitude, double longitude) const {
	double min = numeric_limits<double>::max();
	double distance;
	route_set closest_routes = 0;

	for (unsigned int i = 0; i < MAX_STATIONS; i++) {
		distance = distance_between(this->_parents[i].s_location(), GPS(longitude, latitude));

		if (distance < min) {
			min = distance;
			closest_routes = this->_parents[i].routes();
		}
	}

	// form a string from the bitmask and return
	return str_from_routeset(closest_routes);
}
