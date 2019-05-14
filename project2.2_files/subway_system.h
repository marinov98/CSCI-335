/******************************************************************************
  Title          : subway_system.h
  Author         : Marin Pavlinov Marinov
  Created on     : April 22, 2018
  Description    : Subway System header file
  Purpose        : overidde the _subway_system interface

  Usage          :
  Build with     : c++11
  Modifications  :

******************************************************************************/

#ifndef SUBWAY_SYSTEM_H
#define SUBWAY_SYSTEM_H

#include "_subway_system.h"
#include "hash_table.h"
#include "subway_station.h"
#include <limits>

class SubwaySystem : public _SubwaySystem {
  public:
	SubwaySystem();
	/** add_portal()  adds the given portal to the array of portals
	 *  It also creates a hash table entry for this portal that points to
	 *  its location in the array.
	 *  @param  SubwayPortal [in] portal: an initialized portal
	 *  @return int  1 if successful, 0 if portal is not added.
	 */
	int add_portal(SubwayPortal portal) final;

	/** list_all_stations() lists all subway station names on the given stream
	 *  @param [inout] ostream out is an open output stream
	 */
	void list_all_stations(ostream& out) final;

	/** list_all_portals() lists all portals to a given station on given stream
	 *  @param [inout] ostream is an open output stream
	 *  @param [in]  string station_name is the exact name of a station,
	 *          which must be the name of the set of portal names. These can
	 *          be obtained from the output of list_all_stations().
	 */
	void list_all_portals(ostream& out, string station_name) final;

	/** list_stations_of_route() lists all station names on the given route on
	 *          the given output stream
	 *  @param [inout] ostream is an open output stream
	 *  @param [in]  route_id route is the name of the subway route whose
	 *          stations are to be printed onto the stream
	 */
	void list_stations_of_route(ostream& out, route_id route) final;

	/** form_stations()
	 *  Note: form_stations should be called once after the array of portals
	 *  has been created. It determines which portals are connected to each
	 *  other and forms disjoint sets of connected stations and portals.
	 *  After all sets are formed, it stores the names of the stations that
	 *  name these sets (e.g., if parent trees, the ones at the root)
	 *  in a hash table for station names for fast access.
	 *  Finally, it sets an internal flag to indicate that the sets have been
	 *  computed.
	 *  @return int : number of sets created
	 */
	int form_stations() final;

	/** get_portal() searches for a portal whose name equals name_to_find
	 *  @param string [in]  name_to_find is the portal name to look up
	 *  @param SubwayPortal & [out] is filled with the data from the Portal
	 *         if it is found, or is an empty Portal whose name is ""
	 *  @return bool true if anf only if the portal is found
	 */
	bool get_portal(string name_to_find, SubwayPortal& portal) final;

	/** nearest_portal() returns a string representation of the portal that
	 *  is nearest to the given point
	 *  @param  double [in]  latitude of point
	 *  @param  double [in]  longitude of point
	 *  @return string       portal's name (as defined in subway_portal.h)
	 */
	string nearest_portal(double latitude, double longitude) final;

	/** nearest_routes() returns a string representation of the routes that
	 *  are nearest to the given point
	 *  @param  double [in]  latitude of point
	 *  @param  double [in]  longitude of point
	 *  @return string       representation of set of routes
	 */
	string nearest_routes(double latitude, double longitude) final;

  private:
	/*
	    pre: nothing

	    post: initializes bit mask routes 1-35
	*/
	// void initialize_bit_masks();

	// true when bit masks have been initialized , false when not
	bool initialized = false;

	// private helper method to help with form_stations()
	// unions two subway stations
	/*
	    *Courtesy to professor Weiss' notes
	    on the algorithms for find and union
	*/
	void Union(int root1, int root2);

	// private helper, finds the root of the indicated subway station
	int find(int index);

	/*
	    pre: sets have been formed

	    post: inserts all children indices in the list of children of the roots
	*/
	void add_children();

	/*
	    pre: sets have been formed

	    post: inserts station names of the Stations that are not roots into the
	    ones that are.
	*/

	void add_station_names();

	/*
	    pre: sets have formed

	    post: inserts all SubwayStations that are roots and returns the amount of sets formed

	*/
	int hash_stations();

	// hashtable to store portal names
	HashTable _p_names;

	// using my hashtable to store station names
	HashTable _s_names;

	// array of parent trees
	SubwayStation _parents[MAX_STATIONS];

	// index to keep track of where Stations and bit_masks are inserted
	unsigned int _array_index;

	/*
	    array of bit_masks 36 instead of 35 because I start at 1
	        ith bit -> actual value
	        ex.
	        bit_masks[1] -> 2
	        bit_masks[3] -> 8
	        bit_masks[5] -> 32
	*/
	SubwayRoute bit_masks[NUM_ROUTES_MAX];
};

#endif /* SUBWAY_SYSTEM_H */
