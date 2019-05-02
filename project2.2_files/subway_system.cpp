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
	// create __Itemtype object to be able to use hashtable
	// we dont care about the position because our hastable only looks by key
	__ItemType name(portal.name(), 0);

	/*
	  *Note: my hashtable checks if its an empty string before inserting
	  meaning if the portal was not initialized, it will not be inserted
	*/
	if (0 == this->hash_table.insert(name))
		return 0;
	else
		return 1;
}

void SubwaySystem::list_all_stations(ostream& out) const {}

void SubwaySystem::list_all_portals(ostream& out, string station_name) const {}

void SubwaySystem::list_stations_of_route(ostream& out, route_id route) const {}

int SubwaySystem::form_stations() {}

bool SubwaySystem::get_portal(string name_to_find, SubwayPortal& portal) const {
	__ItemType desired_name(name_to_find, 0);
	if (0 == this->hash_table.find(desired_name))
		return 0;
	else {
		portal.name() = name_to_find;
		return 1;
	}
};

string SubwaySystem::nearest_portal(double latitude, double longitude) const {}

string SubwaySystem::nearest_routes(double latitude, double longitude) const {}
