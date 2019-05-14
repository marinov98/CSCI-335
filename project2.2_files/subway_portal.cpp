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

SubwayPortal::SubwayPortal() :
    _name(""),
    division(""),
    line(""),
    station_name(""),
    _s_latitude(0),
    _s_longitude(0),
    p_routes(0),
    entrance_type(""),
    entry(true),
    exit_only(false),
    vending(false),
    staffing(""),
    staff_hours(""),
    ada(false),
    ada_notes(""),
    free_crossover(false),
    n_s_street(""),
    e_w_street(""),
    corner(""),
    id(1),
    _e_latitude(0),
    _e_longitude(0),
    _s_location({0, 0}),
    _e_location({0, 0}) {
	// cout << "defualt Portal called!" << '\n';
}

SubwayPortal::SubwayPortal(const SubwayPortal& other) :
    _name(other._name),
    division(other.division),
    station_name(other.station_name),
    _s_latitude(other._s_latitude),
    _s_longitude(other._s_longitude),
    p_routes(other.p_routes),
    entrance_type(other.entrance_type),
    entry(other.entry),
    exit_only(other.exit_only),
    vending(other.vending),
    staffing(other.staffing),
    staff_hours(other.staff_hours),
    ada(other.ada),
    ada_notes(other.ada_notes),
    free_crossover(other.free_crossover),
    n_s_street(other.n_s_street),
    e_w_street(other.e_w_street),
    corner(other.corner),
    id(other.id),
    _e_latitude(other._e_latitude),
    _e_longitude(other._e_longitude) {}

SubwayPortal::SubwayPortal(SubwayPortal&& other) noexcept :
    _name(other._name),
    division(other.division),
    station_name(other.station_name),
    _s_latitude(other._s_latitude),
    _s_longitude(other._s_longitude),
    p_routes(other.p_routes),
    entrance_type(other.entrance_type),
    entry(other.entry),
    exit_only(other.exit_only),
    vending(other.vending),
    staffing(other.staffing),
    staff_hours(other.staff_hours),
    ada(other.ada),
    ada_notes(other.ada_notes),
    free_crossover(other.free_crossover),
    n_s_street(other.n_s_street),
    e_w_street(other.e_w_street),
    corner(other.corner),
    id(other.id),
    _e_latitude(other._e_latitude),
    _e_longitude(other._e_longitude) {}

SubwayPortal& SubwayPortal::operator=(const SubwayPortal& other) {
	this->_name = other._name;
	this->division = other.division;
	this->station_name = other.station_name;
	this->_s_latitude = other._s_latitude;
	this->_s_longitude = other._s_longitude;
	this->p_routes = other.p_routes;
	this->entrance_type = other.entrance_type;
	this->entry = other.entry;
	this->exit_only = other.exit_only;
	this->vending = other.vending;
	this->staffing = other.staffing;
	this->staff_hours = other.staff_hours;
	this->ada = other.ada;
	this->ada_notes = other.ada_notes;
	this->free_crossover = other.free_crossover;
	this->n_s_street = other.n_s_street;
	this->e_w_street = other.e_w_street;
	this->corner = other.corner;
	this->id = other.id;
	this->_e_latitude = other._e_latitude;
	this->_e_longitude = other._e_longitude;

	return *this;
}

SubwayPortal& SubwayPortal::operator=(SubwayPortal&& other) noexcept {
	this->_name = other._name;
	this->division = other.division;
	this->station_name = other.station_name;
	this->_s_latitude = other._s_latitude;
	this->_s_longitude = other._s_longitude;
	this->p_routes = other.p_routes;
	this->entrance_type = other.entrance_type;
	this->entry = other.entry;
	this->exit_only = other.exit_only;
	this->vending = other.vending;
	this->staffing = other.staffing;
	this->staff_hours = other.staff_hours;
	this->ada = other.ada;
	this->ada_notes = other.ada_notes;
	this->free_crossover = other.free_crossover;
	this->n_s_street = other.n_s_street;
	this->e_w_street = other.e_w_street;
	this->corner = other.corner;
	this->id = other.id;
	this->_e_latitude = other._e_latitude;
	this->_e_longitude = other._e_longitude;

	return *this;
}
vector<string> SubwayPortal::get_contents(string s) {
	string name("");

	// vector to store contents of each row
	vector<string> collector;

	// reserve space, I use 31 because I know that I will us the first 31 and last 2
	// are just string representations of GPS values
	collector.reserve(31);
	for (const auto& content : s) {
		// we do not need the last two fields
		if (collector.size() >= 31)
			break;
		if (',' != content) {
			name += content;
		}
		else {
			collector.emplace_back(name);
			// reset name to add next field
			name = "";
		}
	}

	return collector;
}

string SubwayPortal::remove_excess(string s) {
	string res("");

	for (unsigned int i = 0; i < s.size(); i++) {
		if (isspace(s[i])) {
			res += " ";
			i++;
			// keep going if there is still white space
			while (isspace(s[i]))
				i++;

			i--;
		}
		else {
			res += s[i];
		}
	}

	return res;
}

string SubwayPortal::create_name(vector<string> dataset) {
	// ensure vector is not empty
	if (dataset.empty())
		return "no data found";

	// assuming data was extracted
	// indices 25-28 contain necessary information to create a new name
	this->n_s_street = dataset[25];
	this->e_w_street = dataset[26];
	this->corner = dataset[27];
	this->id = stoi(dataset[28]);

	// remove excessive whitespaces
	// *NOTE: I add dataset[28] instead of id because I dont want to convert it back to a
	// string
	return remove_excess(this->n_s_street + "," + this->e_w_street + "," + this->corner + ","
	                     + dataset[28]);
}

route_set SubwayPortal::set_routes(vector<string> dataset) {
	route_set routes = 0;
	// avoid shifting errors
	long one = 1;
	// Indeces 5 to 16 contain the necessary information needed to set route bits
	for (int i = 5; i < 16; i++) {
		// ensure a route exists in current index
		if ("" != dataset[i]) {
			int k = routestring2int(dataset[i]);
			// set kth bit
			routes |= (one << k);
		}
	}

	return routes;
}

SubwayPortal::SubwayPortal(string data_row) {
	vector<string> data = get_contents(data_row);

	// this will intitialize name,NS/EW street,corner,id and check for emptiness
	// Indeces (25-28)
	this->_name = create_name(data);

	// Initialize all other fields from data
	// Indeces (0-2)
	this->division = data[0];
	this->line = data[1];
	this->station_name = data[2];

	/*
	    LOCATION INITIALIZATION {3-4,29-30}
	*/
	// station
	this->_s_latitude = stod(data[3]);
	this->_s_longitude = stod(data[4]);
	this->_s_location = GPS(this->_s_longitude, this->_s_latitude);

	// entrance
	this->_e_latitude = stod(data[29]);
	this->_e_longitude = stod(data[30]);
	this->_e_location = GPS(this->_e_longitude, this->_e_latitude);

	/*
	    ROUTES (5-15)
	*/
	this->p_routes = set_routes(data);

	/*
	    OTHERS (16-24)
	*/
	this->entrance_type = data[16];
	this->entry = (data[17] == "YES");
	this->exit_only = (data[18] == "YES");
	this->vending = (data[19] == "YES");
	this->staffing = data[20];
	this->staff_hours = data[21];
	this->ada = (data[22] == "TRUE");
	this->ada_notes = data[23];
	this->free_crossover = (data[24] == "TRUE");
}

double SubwayPortal::distance_from(double latitude, double longitude) {
	/*
	 construct GPS object to:
	 i) check if coardinates are valid
	 ii) use haversine function I defined in gps.h
	*/
	return distance_between(this->_s_location, GPS(longitude, latitude));
}

double distance_between(SubwayPortal portal1, SubwayPortal portal2) {
	// distance_between with GPS parameters uses haversine function
	return distance_between(portal1._e_location, portal2._e_location);
}

bool same_routes(SubwayPortal portal1, SubwayPortal portal2) {
	return portal1.p_routes == portal2.p_routes;
}

bool same_station(SubwayPortal portal1, SubwayPortal portal2) {
	return portal1.station_name == portal2.station_name;
}

ostream& operator<<(ostream& out, SubwayPortal e) {
	out << "coordinates of entrance: " << e._e_location;
	return out;
}

string SubwayPortal::name() const {
	return this->_name;
}

bool SubwayPortal::can_access(route_set route) const {
	return (0 != (this->p_routes & route));
}

GPS SubwayPortal::p_location() const {
	return this->_e_location;
}

GPS SubwayPortal::s_location() const {
	return this->_s_location;
}

route_set SubwayPortal::routes() const {
	return this->p_routes;
}
