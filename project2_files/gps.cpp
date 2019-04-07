
/******************************************************************************
  Title          : gps.cpp
  Author         : Marin Pavlinov Marinov
  Created on     : April 3, 2019
  Description    : cpp file for the gps class
  Purpose        : Implement the gps class
  Usage          :
  Build with     : c++11
********************************************************************************/

#include "gps.h"


GPS::GPS(double lon, double lat) throw (BadPoint()) {
    // checking boundaries for latitude
    if (lat <= -90 || lat >= 90)
	throw (BadPoint());
    // checking boundaries for longitude
    if (lon <= -180 || lon >= 180)
	throw (BadPoint());

    // If code comes here, it means the values are valid
    this->longitude = move(lon);
    this->latitude = move(lat);
 }

GPS::GPS(const GPS& location) {
    // checking boundaries for latitude
    if (location.latitude <= -90 || location.latitude >= 90)
	throw BadPoint();

    // checking boundaries for longitude
    if (location.longitude <= -180 || location.longitude >= 180)
	throw BadPoint();

    // If code comes here, values are valid
    this->longitude = location.longitude;
    this->latitude = location.latitude;
    
}

void GPS::operator=(const GPS& location) {
    this->longitude = location.longitude;
    this->latitude = location.latitude;
}


double haversine(GPS point1, GPS point2) {
    const double R = 6372.8; // radius of earth in km
    const double TO_RAD = M_PI / 180.0; // conversion of degrees to radians

    // latitude conversion to radians
    point1.latitude = TO_RAD * point1.latitude;
    point2.latitude = TO_RAD * point2.latitude;

    // longitude conversion to radians
    point1.longitude = TO_RAD * point1.longitude;
    point2.longitude = TO_RAD * point2.longitude;

    // distances
    double dLat = (point2.latitude - point1.latitude)/2;
    double dLon = (point2.longitude - point1.longitude)/2;

    double a = sin(dLat);
    double b = sin(dLon);

    return 2 * R * asin(sqrt(a*a + cos(point1.latitude)*cos(point2.latitude)*b*b));
}

double distance_between(GPS point1, GPS point2) {
    // utilize our private method to properly convert and calculate the distance 
   return haversine(point1, point2);  
}

ostream& operator<<(ostream& out, GPS point) {
    out << point.longitude << point.latitude;

    return out;
}

