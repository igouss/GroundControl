#include <math.h>
#include "LatLon.h"

namespace naxsoft {

/**
 *  Convert to degrees from radians
 */
double LatLon::angleToRadians(double angle) {
	return (angle / 180) * M_PI;
}

/**
 *  Convert to radians from degrees
 */
double LatLon::radToDegrees(double radians)
{
    return radians * (180 / M_PI);
}

double LatLon::getBearing(double srcLat, double srcLon, double destLat, double destLon) {
	  double lat1 = angleToRadians(srcLat);
	  double lat2 = angleToRadians(destLat);
	  double dLon = angleToRadians(destLon - srcLon);

	  double y = sin(dLon) * cos(lat2);
	  double x = cos(lat1)*sin(lat2) - sin(lat1)*cos(lat2)*cos(dLon);
	  double brng = radToDegrees(atan2(y, x));
	  if(brng < 0) {
		  brng += 360;
	  } else if(brng > 360) {
		  brng -= 360;
	  }
	  return brng;
}

void LatLon::decimalDegreesToDMS(double original, dmsData* dms) {

	int  degree = original;
	double sec;
	long min;
	double doublemin = original - degree;
	doublemin *= 60;

	min = doublemin;
	doublemin -= min;
	doublemin *= 60;

	sec = doublemin;

	dms->degree = degree;
	dms->min = min;
	dms->sec = sec;
}


/**
 * This uses the ‘haversine’ formula to calculate the great-circle distance
 * between two points – that is, the shortest distance over the earth’s surface –
 * giving an ‘as-the-crow-flies’ distance between the points (ignoring any hills, of course!).
 * http://www.movable-type.co.uk/scripts/latlong.html
 */
double LatLon::calcDistance(double srcLat, double srcLon, double destLat, double destLon) {
	int R = 6371; // km

	double lat1 = angleToRadians(srcLat);
	double lon1 = angleToRadians(srcLon);
	double lat2 = angleToRadians(destLat);
	double lon2 = angleToRadians(destLon);
	double dLat = lat2 - lat1;
	double dLon = lon2 - lon1;

	double a = sin(dLat/2) * sin(dLat/2) +  cos(lat1) * cos(lat2) * sin(dLon/2) * sin(dLon/2);
	double c = 2 * atan2(sqrt(a), sqrt(1-a));
	double d = R * c;

	return d;
}

}
