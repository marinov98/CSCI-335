/******************************************************************************
Title          : subway_station.cpp
Author         : Marin Pavlinov Marinov
Created on     : April 22, 2018
Description    : cpp file for Subway Station
Purpose        : Implements subway Station
Usage          :
Build with     :c++11
Modifications  :

******************************************************************************/

#include "subway_station.h"

SubwayStation::SubwayStation() : m_parent_id(-1), portal_unique_name("") {}

SubwayStation::SubwayStation(SubwayPortal portal) :
    portal(portal),
    portal_unique_name(portal.name()),
    m_parent_id(-1) {
	// insert into set of station names
	// because its a set, it will not store dublicates
	this->m_station_names.emplace(portal.station_name);
}

void SubwayStation::set_parent(int newparent) {
	this->m_parent_id = newparent;
}

void SubwayStation::add_child(int child) {
	this->children.emplace_back(child);
}

bool connected(SubwayStation s1, SubwayStation s2) {
	// according to specifications two stations are connected if:
	// the set of routes is identical
	// distance between them is at most 0.28
	return (s1.portal.routes() == s2.portal.routes())
	       || distance_between(s1.portal.s_location(), s2.portal.s_location()) <= 0.28;
}

int SubwayStation::add_station_name(string newname) {
	// set returns a pair<iterator,bool> indicated whether insetion was successful
	if (!this->m_station_names.emplace(newname).second)
		return 0;

	return 1;
}

list<string> SubwayStation::names() const {
	list<string> names;

	// store station names in a list and return
	for (const auto& name : this->m_station_names)
		names.emplace_back(name);

	return names;
}

string SubwayStation::primary_name() const {
	// in case nothing was ever added to the set
	// avoids seg faults
	if (0 == this->m_station_names.size())
		return "";

	return *(this->m_station_names).begin();
}

int SubwayStation::parent_id() const {
	return this->m_parent_id;
}

list<int> SubwayStation::portal_list() const {
	return this->children;
}

string SubwayStation::portal_name() const {
	return this->portal_unique_name;
}

void SubwayStation::get_portal(SubwayPortal& portal) const {
	portal = this->portal;
}
