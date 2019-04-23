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

SubwayPortal::SubwayPortal() {}

SubwayPortal::SubwayPortal(string data_row) {}

double SubwayPortal::distance_from(double latitude, double longitude) {}

double distance_between(SubwayPortal portal1, SubwayPortal portal2) {}

bool same_routes(SubwayPortal portal1, SubwayPortal portal2) {}

bool same_station(SubwayPortal portal1, SubwayPortal portal2) {}

ostream& operator<<(ostream& out, SubwayPortal e) {}

string SubwayPortal::name() const {}

bool SubwayPortal::can_access(route_set route) const {}

GPS SubwayPortal::p_location() const {}

GPS SubwayPortal::s_location() const {}

route_set SubwayPortal::routes() const {}