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

#include "gps.h"
#include "subway_route.h"

#include <string>
#include <vector>

using namespace std;

struct Invalid_Portal_Data {};

// class SubwayStation;

class _SubwayPortal {
  public:
	/** returns the distance between station and a gps location  */
	virtual double distance_from(double latitude, double longitude) = 0;

	/*  Accessor  Functions */
	/**  name() returns name of portal as a unique string
	 */
	virtual string name() const = 0;

	/** can_access() returns true if given route is accessible
	 *  @param route_set [in]  a bitstring with a 1 bit for route
	 *  @return bool  true iff route is accessible from this portal
	 */
	virtual bool can_access(route_set route) const = 0;

	/**  p_location() returns GPS location of portal  */
	virtual GPS p_location() const = 0;

	/**  s_location() returns GPS location of portal's station */
	virtual GPS s_location() const = 0;

	/**  routes() returns route set of portal */
	virtual route_set routes() const = 0;
};

#endif /* __SUBWAY_PORTAL_H__ */
