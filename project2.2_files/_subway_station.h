/******************************************************************************
  Title          : _subway_station.h
  Author         : Marin Pavlinov Marinov
  Created on     : April 22, 2018
  Description    : Interface file for the SubwayStation object Credit to Professor Stewart Weiss
  Purpose        : Encapsulates data and methods of a subway station
  Usage          :
  Build with     : no build
  Modifications  : removed constructors and private fields because this is an interface

******************************************************************************/

#ifndef __SUBWAY_STATION_H__
#define __SUBWAY_STATION_H__

#include "subway_portal.h"
#include <iostream>
#include <list>
#include <set>
#include <string>

using namespace std;

class _SubwayStation {
  public:
	/** set_parent() sets the parent id of the station
	 * @param int [in] the id of the parent
	 */
	virtual void set_parent(int newparent) = 0;
	/** add_child() adds a new child to the station's list of children
	 * @param int [in] the index of the child to add
	 */
	virtual void add_child(int child) = 0;
	/** A friend function that determines when two stations are connected
	 * @param SubwayStation [in] s1
	 * @param SubwayStation [in] s2
	 * @return bool true iff s1 and s2 are connected according to rules defined
	 * in the assignment specification
	 */
	/*  * CONNECTED REMOVED BECAUSE I MADE THIS AN ABSTRACT CLASS
	 */
	/** add_station_name() adds a new name to station
	 * @Note: It does not add a name if it is already in the set of names for
	 * the station.
	 * @param string [in] newname is name to be added
	 * @return 1 if name is added and 0 if not
	 */
	virtual int add_station_name(string newname) = 0;
	/** names() returns a list of the names of the station as a list of strings
	 */
	virtual list<string> names() const = 0;
	// primary_name() is the first station name in its set of names
	virtual string primary_name() const = 0;
	// parent_id() is the index in the array of the parent of the station
	virtual int parent_id() const = 0;
	/** portal_list() returns a list of the ids in the list of the portals in
	 * this station set
	 */
	virtual list<int> portal_list() const = 0;
	// returns the name of the embedded portal
	virtual string portal_name() const = 0;
	// returns the portal that is embedded in this station object
	virtual void get_portal(SubwayPortal&) const = 0;
};

#endif