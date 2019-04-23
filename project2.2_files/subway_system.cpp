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

int SubwaySystem::add_portal(SubwayPortal portal) {}

void SubwaySystem::list_all_stations(ostream& out) const {}

void SubwaySystem::list_all_portals(ostream& out, string station_name) const {}

void SubwaySystem::list_stations_of_route(ostream& out, route_id route) const {}

int SubwaySystem::form_stations() {}

bool SubwaySystem::get_portal(string name_to_find, SubwayPortal& portal) const {}

string SubwaySystem::nearest_portal(double latitude, double longitude) const {}

string SubwaySystem::nearest_routes(double latitude, double longitude) const {}
