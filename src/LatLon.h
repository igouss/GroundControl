#ifndef LATLON_H_
#define LATLON_H_

namespace naxsoft {

typedef struct {
	int  degree;
	long min;
	double sec;
} dmsData;

class LatLon {
public:
	/** Converts numeric degrees to radians */
	static double angleToRadians(double angle);

	/** Converts radians to numeric (signed) degrees */
	static double radToDegrees(double radians);

	/**
	 * Returns the (initial) bearing from this point to the supplied point, in degrees
	 *   see http://williams.best.vwh.net/avform.htm#Crs
	 *
	 * @param   {LatLon} point: Latitude/longitude of destination point
	 * @returns {Number} Initial bearing in degrees from North
	 */
	static double getBearing(double srcLat, double srcLon, double destLat, double destLon);

	/**
	 * Returns the distance from this point to the supplied point, in km
	 * (using Haversine formula)
	 *
	 * from: Haversine formula - R. W. Sinnott, "Virtues of the Haversine",
	 *       Sky and Telescope, vol 68, no 2, 1984
	 *
	 * @param   {LatLon} point: Latitude/longitude of destination point
	 * @param   {Number} [precision=4]: no of significant digits to use for returned value
	 * @returns {Number} Distance in km between this point and destination point
	 */
	static double calcDistance(double lat1, double lon1, double lat2, double lon2);

	/**
	 * Convert latitude and longitude between decimal degrees and degrees, minutes, and seconds
	 */
	static void decimalDegreesToDMS(double original, dmsData* dms);
};

}

#endif /* LATLON_H_ */
