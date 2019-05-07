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
		// create subway station object
		SubwayStation object_to_insert(portal);

		int res =
		    this->_p_names.insert(__ItemType(object_to_insert.portal_name(), this->p_array_index));

		if (-1 == res)
			return 0;
		else {
			// store in array of parent trees
			this->_parents[this->p_array_index] = portal;
			this->bit_masks[this->p_array_index] = portal.routes();
			this->p_array_index++;
			return 1;
		}
	}

	return 0;
}

void SubwaySystem::list_all_stations(ostream& out) {
	out << _s_names.listall(out);
}

void SubwaySystem::list_all_portals(ostream& out, string station_name) {
	int position = this->_s_names.find(__ItemType(station_name, 0));
	// in case item was not found
	if (position != -1) {
		list<string> names = this->_parents[position].names();

		for (const auto& name : names) {
			out << name;
		}
	}
}

void SubwaySystem::list_stations_of_route(ostream& out, route_id route) {
	// probably wrong to be fixed later
	for (unsigned int i = 0; i < this->p_array_index; i++) {
		// check if the routsets match
		if ((this->bit_masks[i] & routestring2int(route)) != 0) {
			list<string> names = this->_parents[i].names();
			for (const auto& name : names) {
				out << name;
			}
		}
	}
}

int SubwaySystem::find(int index) {
	if (this->_parents[index].parent_id() < 0)
		return index;
	else
		return find(this->_parents[index].parent_id());
}

void SubwaySystem::Union(int root1, int root2) {
	if (root1 != root2) {
		if (this->_parents[root2].parent_id() < this->_parents[root1].parent_id()) {
			// root 2 is deeper
			this->_parents[root2].set_parent(this->_parents[root2].parent_id()
			                                 + this->_parents[root1].parent_id());

			// this->_parents[root1] = this->_parents[root2];
			this->_parents[root1].set_parent(root2);
		}
		else {
			// root1 is deeper
			this->_parents[root1].set_parent(this->_parents[root1].parent_id()
			                                 + this->_parents[root2].parent_id());

			// this->_parents[root2] = this->_parents[root1];
			this->_parents[root2].set_parent(root1);
		}
	}
}

int SubwaySystem::insert_stations() {
	int sets = 0;
	for (unsigned int i = 0; i < this->p_array_index; i++) {
		// make sure we are inserting routes
		if (this->_parents[i].parent_id() < 0) {
			// get its position in the array
			int position = this->_p_names.find(__ItemType(this->_parents[i].portal_name(), 0));

			// get list of stations
			list<string> stations = this->_parents[i].names();
			for (const auto& station : stations) {
				// store in hashtable
				this->_s_names.insert(__ItemType(station, position));
				sets++;
			}
		}
	}

	return sets;
}

int SubwaySystem::form_stations() {
	// check if array of portals was created
	// if p_array index is still 0, that means nothing was inserted yet
	if (0 == this->p_array_index)
		return 0;

	// Union the sets and do stuff down here
	for (unsigned int i = 0; i < (this->p_array_index - 1); i++) {
		for (unsigned int j = i + 1; j < this->p_array_index; j++) {
			// check for connectivity
			if (connected(this->_parents[i], this->_parents[j])) {
				int root1 = find(i);
				int root2 = find(j);

				Union(root1, root2);
			}
		}
	}

	int sets_created = insert_stations();

	return sets_created;
}

bool SubwaySystem::get_portal(string name_to_find, SubwayPortal& portal) {
	// if its not found, we cannot get the name
	// Since I modified find in my hash table to return the position instead of just
	// 1 , I can now use it find the portal in the parent trees array
	int res = this->_p_names.find(__ItemType(name_to_find, 0));

	if (-1 == res)
		return false;

	// copy data into parameter
	SubwayPortal portal_to_copy;
	this->_parents[res].get_portal(portal_to_copy);
	portal = portal_to_copy;
	return true;
};

string SubwaySystem::nearest_portal(double latitude, double longitude) {
	double min = numeric_limits<double>::max();

	string closest_portal("");
	double distance;

	for (unsigned int i = 0; i < MAX_STATIONS; i++) {
		SubwayPortal portal;
		this->_parents[i].get_portal(portal);
		distance = distance_between(portal.p_location(), GPS(longitude, latitude));

		if (distance < min) {
			min = distance;
			closest_portal = portal.name();
		}
	}

	return closest_portal;
}

string SubwaySystem::nearest_routes(double latitude, double longitude) {
	double min = numeric_limits<double>::max();
	double distance;
	route_set closest_routes = 0;

	for (unsigned int i = 0; i < MAX_STATIONS; i++) {
		SubwayPortal portal;
		this->_parents[i].get_portal(portal);
		distance = distance_between(portal.s_location(), GPS(longitude, latitude));

		if (distance < min) {
			min = distance;
			closest_routes = portal.routes();
		}
	}

	// form a string from the bitmask and return
	return str_from_routeset(closest_routes);
}
