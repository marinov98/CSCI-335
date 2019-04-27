/******************************************************************************
  Title          : subway_portal.h
  Author         : Marin Pavlinov Marinov
  Created on     : April 22, 2018
  Description    : Subway Portal header
  Purpose        : override the interface
  Usage          :
  Build with     : c++11
  Modifications  :

******************************************************************************/

#ifndef SUBWAY_PORTAL_H
#define SUBWAY_PORTAL_H

#include "_subway_portal.h"

class SubwayPortal : public _SubwayPortal {
  public:
	SubwayPortal();
	SubwayPortal(string data_row);

	/** returns the distance between station and a gps location  */
	double distance_from(double latitude, double longitude);

	/** returns the distance between the two portals  */
	friend double distance_between(SubwayPortal portal1, SubwayPortal portal2);

	/** returns true if the two portals have the exact same set of routes  */
	friend bool same_routes(SubwayPortal portal1, SubwayPortal portal2);

	/** returns true if the two portals belong to the same station */
	friend bool same_station(SubwayPortal portal1, SubwayPortal portal2);

	friend ostream& operator<<(ostream& out, SubwayPortal e);

	friend class SubwayStation;

	/*  Accessor  Functions */
	/**  name() returns name of portal as a unique string
	 */
	string name() const;

	/** can_access() returns true if given route is accessible
	 *  @param route_set [in]  a bitstring with a 1 bit for route
	 *  @return bool  true iff route is accessible from this portal
	 */
	bool can_access(route_set route) const;

	/**  p_location() returns GPS location of portal  */
	GPS p_location() const;

	/**  s_location() returns GPS location of portal's station */
	GPS s_location() const;

	/**  routes() returns route set of portal */
	route_set routes() const;

  private:
	/*
	     pre: nothing

	     post: takes row from data and turns it into an unique name
	*/
	string create_name(string input);

	// longitude and latitude of the portal
	GPS _location;

	// name of the portal
	string _name;
};

#endif /* SUBWAY_PORTAL_H */
