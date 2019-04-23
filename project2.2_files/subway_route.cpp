/******************************************************************************
  Title          : subway_routes.cpp
  Author         : Marin Pavlinov Marinov
  Created on     : April 22, 2018
  Description    : Interface file for the SubwayRoute object
  Purpose        : implements subway_route
  Usage          :
  Build with     : c++11
  Modifications  :

******************************************************************************/

#include "subway_route.h"

/*******************************************************************************
 *                    Functions related to subway routes                        *
 ******************************************************************************/

bool is_route_id(string s) {}

string str_from_routeset(route_set s) {}

int routesstring2int(string s) {}

string int2route_id(int k) {}

/*******************************************************************************
 *                           SubwayRoute Class                                  *
 ******************************************************************************/

SubwayRoute::SubwayRoute() {}

list<int> SubwayRoute::station_list() const {}

void SubwayRoute::add_station_to_route(int station_id) {}

route_set SubwayRoute::get_routeset() const {}
