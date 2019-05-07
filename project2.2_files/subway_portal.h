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

	     post: takes row from data and stores contents into a vector
	*/
	vector<string> get_contents(string input);

	// takes appropraite fields and creates unique name from vector
	string create_name(vector<string> dataset);

	// removes excessive white whitespace
	string remove_excess(string s);

	// sets appropriate bits for routes
	route_set set_routes(vector<string> dataset);

	// name of the portal
	string _name;

	/*
	    FIELDS BELOW ARE MEANT TO CORRESPOND TO DATASET
	*/
	string division;
	string line;
	string station_name;

	// station longitude and latitude
	double _s_latitude;
	double _s_longitude;

	// routes 1-11
	route_set p_routes;

	// entrance and ADA
	string entrance_type;
	bool entry;
	bool exit_only;
	bool vending;
	string staffing;
	string staff_hours;
	bool ada;
	string ada_notes;
	bool free_crossover;

	// fields necessary for naming
	string n_s_street;
	string e_w_street;
	string corner;
	int id;

	double _e_latitude;
	double _e_longitude;

	// station location
	GPS _s_location;

	// entrance location
	GPS _e_location;
};

#endif /* SUBWAY_PORTAL_H */
