/******************************************************************************
  Title          : _subway_system.h
  Author         : Stewart Weiss
  Created on     : April 18, 2018
  Description    : Interface file for the SubwaySystem object
  Purpose        : Encapsulates data and methods of a subway system
  Usage          :
  Build with     : no build
  Modifications  :

******************************************************************************/

#ifndef __SUBWAY_SYSTEM_H__
#define __SUBWAY_SYSTEM_H__

#include "subway_portal.h"
#include "subway_route.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#define MAX_STATIONS 2048

using namespace std;

class _SubwaySystem {
  public:
	/** add_portal()  adds the given portal to the array of portals
	 *  It also creates a hash table entry for this portal that points to
	 *  its location in the array.
	 *  @param  SubwayPortal [in] portal: an initialized portal
	 *  @return int  1 if successful, 0 if portal is not added.
	 */
	virtual int add_portal(SubwayPortal portal) = 0;

	/** list_all_stations() lists all subway station names on the given stream
	 *  @param [inout] ostream out is an open output stream
	 */
	virtual void list_all_stations(ostream& out) = 0;

	/** list_all_portals() lists all portals to a given station on given stream
	 *  @param [inout] ostream is an open output stream
	 *  @param [in]  string station_name is the exact name of a station,
	 *          which must be the name of the set of portal names. These can
	 *          be obtained from the output of list_all_stations().
	 */
	virtual void list_all_portals(ostream& out, string station_name) = 0;

	/** list_stations_of_route() lists all station names on the given route on
	 *          the given output stream
	 *  @param [inout] ostream is an open output stream
	 *  @param [in]  route_id route is the name of the subway route whose
	 *          stations are to be printed onto the stream
	 */
	virtual void list_stations_of_route(ostream& out, route_id route) = 0;

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
	virtual int form_stations() = 0;

	/** get_portal() searches for a portal whose name equals name_to_find
	 *  @param string [in]  name_to_find is the portal name to look up
	 *  @param SubwayPortal & [out] is filled with the data from the Portal
	 *         if it is found, or is an empty Portal whose name is ""
	 *  @return bool true if anf only if the portal is found
	 */
	virtual bool get_portal(string name_to_find, SubwayPortal& portal) = 0;

	/** nearest_portal() returns a string representation of the portal that
	 *  is nearest to the given point
	 *  @param  double [in]  latitude of point
	 *  @param  double [in]  longitude of point
	 *  @return string       portal's name (as defined in subway_portal.h)
	 */
	virtual string nearest_portal(double latitude, double longitude) = 0;

	/** nearest_routes() returns a string representation of the routes that
	 *  are nearest to the given point
	 *  @param  double [in]  latitude of point
	 *  @param  double [in]  longitude of point
	 *  @return string       representation of set of routes
	 */
	virtual string nearest_routes(double latitude, double longitude) = 0;
};

#endif /* __SUBWAY_SYSTEM_H__ */
