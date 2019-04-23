/******************************************************************************
Title          : subway_station.cpp
Author         : Marin Pavlinov Marinov
Created on     : April 22, 2018
Description    : cpp file for Subway Station
Purpose        : Implements subway Station
Usage          :
Build with     : no build
Modifications  :

******************************************************************************/

#include "subway_station.h"

SubwayStation::SubwayStation() {}

SubwayStation::SubwayStation(SubwayPortal portal) {}

void SubwayStation::set_parent(int newparent) {}

void SubwayStation::add_child(int child) {}

bool connected(SubwayStation s1, SubwayStation s2) {}

int SubwayStation::add_station_name(string newname) {}

list<string> SubwayStation::names() const {}

string SubwayStation::primary_name() const {}

int SubwayStation::parent_id() const {}

list<int> SubwayStation::portal_list() const {}

string SubwayStation::portal_name() const {}

void SubwayStation::get_portal(SubwayPortal&) const {}
