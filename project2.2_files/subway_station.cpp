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

SubwayStation::SubwayStation() {
	this->m_parent_id = 0;
	this->portal_unique_name = "";
	// some initialization more :
}

SubwayStation::SubwayStation(SubwayPortal portal) {
	this->portal = portal;
	this->portal_unique_name = portal.name();

	// insert into set of station names
	// because its a hash set, it will not store dublicates
	this->m_station_names.insert(portal.station_name);

	// id insertion
	this->children.push_back(portal.id);
}

void SubwayStation::set_parent(int newparent) {
	this->m_parent_id = newparent;
}

void SubwayStation::add_child(int child) {
	this->children.push_back(child);
}
bool connected(SubwayStation s1, SubwayStation s2) {
	// according to specifications two stations are connected if:
	// the set of routes is identical
	// distance between them is at most 0.28
	return (s1.portal.routes() == s2.portal.routes())
	       && distance_between(s1.portal.s_location(), s2.portal.s_location()) <= 0.28;
}

int SubwayStation::add_station_name(string newname) {
	// if its found, we do not need to insert
	if (this->m_station_names.find(newname) != m_station_names.end())
		return 0;
	else {
		this->m_station_names.insert(newname);
		return 1;
	}
}

list<string> SubwayStation::names() const {
	list<string> names;
	// store station names in a list and return
	for (const auto& name : this->m_station_names)
		names.push_back(name);

	return names;
}

string SubwayStation::primary_name() const {
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
