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

SubwaySystem::SubwaySystem() {
	// NOTE : my mapping begins at 1 so my routes should begin at 1 NOT 0
	for (unsigned int i = 1; i < 36; i++) {
		this->bit_masks[i].routes = 1 << i;
	}
}

int SubwaySystem::add_portal(SubwayPortal portal) {
	// make sure we have not passed our limit
	if (this->_array_index < MAX_STATIONS) {
		// create subway station object
		SubwayStation object_to_insert(portal);

		int res =
		    this->_p_names.insert(__ItemType(object_to_insert.portal_name(), this->_array_index));

		if (-1 == res)
			return 0;
		else {
			// store in array of parent trees
			this->_parents[this->_array_index] = object_to_insert;
			// add to routes
			for (unsigned int i = 1; i < 36; i++) {
				bool bit = this->bit_masks[i].routes & portal.routes();
				if (bit) {
					this->bit_masks[i].add_station_to_route(this->_array_index);
				}
			}

			this->_array_index++;
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
		// cout portal of current object
		out << this->_parents[position].portal_name();

		// get the indeces of the children of that station that have connected portals
		list<int> meddling_kids = this->_parents[position].portal_list();

		for (const auto& trouble_maker : meddling_kids) {
			out << this->_parents[trouble_maker].portal_name();
		}
	}
}

void SubwaySystem::list_stations_of_route(ostream& out, route_id route) {
	// probably wrong to be fixed later
	/*
	 * NOTE I use array index instead of MAX_STATIONS in my for loops becuase
	 * That is how many objects I have inserted and searching anything after the _array_index
	 * Will be some empty SubwayStation object
	 */
	list<int> stations_of_route;
	for (int i = 1; i < 36; i++) {
		// routestring2int returns an int denoting which bit is 1 not the actual bit and the index
		// of bit masks is the position of the bit so we can just compare the index to the route and
		// then we know that that ith bit is where the route is 1
		if (i == routestring2int(route)) {
			stations_of_route = this->bit_masks[i].station_list();
			break;
		}
	}

	// from each station get, its list of names
	// the second for-range loop is in case that station is a parent
	for (const auto& station_index : stations_of_route) {
		list<string> station_names = this->_parents[station_index].names();

		for (const auto& station_name : station_names) {
			out << station_name;
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

			this->_parents[root1].set_parent(root2);
		}
		else {
			// root1 is deeper
			this->_parents[root1].set_parent(this->_parents[root1].parent_id()
			                                 + this->_parents[root2].parent_id());

			this->_parents[root2].set_parent(root1);
		}
	}
}

void SubwaySystem::add_children() {
	for (unsigned int i = 0; i < this->_array_index; i++) {
		// ensure its a child
		if (this->_parents[i].parent_id() > 0)
			this->_parents[find(i)].add_child(i);
	}
}

void SubwaySystem::add_station_names() {
	for (unsigned int i = 0; i < this->_array_index; i++) {
		// ensure index is a root
		if (this->_parents[i].parent_id() < 0) {
			list<int> kids = this->_parents[i].portal_list();
			for (const auto& brat : kids) {
				/*
				    As mentioned in the pdf list of children can become
				        invalid if we change it every time we union. Now that
				        all sets are formed every station thats not a root will have
				        only one station in their set of station names and that will
				        be the sets primary_name
				*/
				if (this->_parents[brat].primary_name() != "")
					this->_parents[i].add_station_name(this->_parents[brat].primary_name());
			}
		}
	}
}

int SubwaySystem::hash_stations() {
	int sets = 0;
	for (unsigned int i = 0; i < this->_array_index; i++) {
		// find an index that is a root
		if (this->_parents[i].parent_id() < 0) {
			// get its position in the array
			int position = i;
			// every time we come by a root, we know its a set
			// the number of roots is the same as the amount of sets created
			sets++;

			// get list of stations
			list<string> stations = this->_parents[i].names();
			for (const auto& station_name : stations) {
				// store in hashtable
				this->_s_names.insert(__ItemType(station_name, position));
			}
		}
	}

	return sets;
}

int SubwaySystem::form_stations() {
	// check if array of portals was created
	// if hash table is empty then the array of portals was never initialized
	if (this->_p_names.empty())
		return 0;

	// Form sets
	for (unsigned int i = 0; i < (this->_array_index - 1); i++) {
		for (unsigned int j = i + 1; j < this->_array_index; j++) {
			// check for connectivity
			if (connected(this->_parents[i], this->_parents[j])) {
				int root1 = find(i);
				int root2 = find(j);

				Union(root1, root2);
			}
		}
	}

	// forms proper lists of children
	add_children();

	// utilize the lists of children to insert the station names
	add_station_names();

	// insert the sets of stations names of the roots into my hashtable
	int sets_created = hash_stations();

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

	for (unsigned int i = 0; i < this->_array_index; i++) {
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
