/******************************************************************************
  Title          : _subway_portal.h
  Author         : Stewart Weiss
  Created on     : April 18, 2018
  Description    : Interface file for the SubwayPortal object
  Purpose        : Encapsulates data and methods of a subway portal
  Usage          :
  Build with     :
  Modifications  :

******************************************************************************/




#ifndef __SUBWAY_PORTAL_H__
#define __SUBWAY_PORTAL_H__


#include <string>
#include <vector>
#include "gps.h"
#include "subway_route.h"




using namespace std;


struct Invalid_Portal_Data {};

class SubwayStation;

class SubwayPortal
{
public:
    SubwayPortal();
    SubwayPortal( string data_row );

    /** returns the distance between station and a gps location  */
    double distance_from( double latitude, double longitude);

    /** returns the distance between the two portals  */
    friend double distance_between( SubwayPortal portal1,
                                    SubwayPortal portal2);



    /** returns true if the two portals have the exact same set of routes  */
    friend bool same_routes( SubwayPortal portal1,
                             SubwayPortal portal2);

    /** returns true if the two portals belong to the same station */
    friend bool same_station( SubwayPortal portal1,
                              SubwayPortal portal2);

    friend ostream & operator<< ( ostream & out, SubwayPortal e);

    friend class SubwayStation;

    /*  Accessor  Functions */
    /**  name() returns name of portal as a unique string
     */
    string name()  const;

    /** can_access() returns true if given route is accessible
     *  @param route_set [in]  a bitstring with a 1 bit for route
     *  @return bool  true iff route is accessible from this portal
     */
    bool   can_access( route_set route ) const;

    /**  p_location() returns GPS location of portal  */
    GPS    p_location() const;

    /**  s_location() returns GPS location of portal's station */
    GPS    s_location() const;

    /**  routes() returns route set of portal */
    route_set routes() const;

};

#endif /* __SUBWAY_PORTAL_H__ */

