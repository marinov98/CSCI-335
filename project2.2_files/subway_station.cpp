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
	this->m_parent_id = -1;
	this->portal_unique_name = "";
	// some initialization more :
}

SubwayStation::SubwayStation(SubwayPortal portal) {
	this->portal = portal;
}

void SubwayStation::set_parent(int newparent) {}

void SubwayStation::add_child(int child) {}

bool connected(SubwayStation s1, SubwayStation s2) {}

int SubwayStation::add_station_name(string newname) {
	// store original size in temp variable
	int size = m_station_names.size();

	m_station_names.insert(newname);
	// if size has not changed then it was not inserted properly
	if (size == m_station_names.size())
		return 0;
	else
		return 1;
}

list<string> SubwayStation::names() const {}

string SubwayStation::primary_name() const {}

int SubwayStation::parent_id() const {}

list<int> SubwayStation::portal_list() const {}

string SubwayStation::portal_name() const {
	return this->portal_unique_name;
}

void SubwayStation::get_portal(SubwayPortal& portal) const {
	portal = this->portal;
}
