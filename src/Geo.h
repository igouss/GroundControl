#ifndef GEO_H_
#define GEO_H_

namespace naxsoft {
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/*  Geodesy representation conversion functions (c) Chris Veness 2002-2010                        */
/*   - www.movable-type.co.uk/scripts/latlong.html                                                */
/*                                                                                                */
/*  Sample usage:                                                                                 */
/*    var lat = Geo.parseDMS('51° 28′ 40.12″ N');                                                 */
/*    var lon = Geo.parseDMS('000° 00′ 05.31″ W');                                                */
/*    var p1 = new LatLon(lat, lon);                                                              */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

struct posn {
  int deg, min, sec;
};

class Geo {
public:
	/**
	 * Parses string representing degrees/minutes/seconds into numeric degrees
	 *
	 * This is very flexible on formats, allowing signed decimal degrees, or deg-min-sec optionally
	 * suffixed by compass direction (NSEW). A variety of separators are accepted (eg 3º 37' 09"W)
	 * or fixed-width format without separators (eg 0033709W). Seconds and minutes may be omitted.
	 * (Note minimal validation is done).
	 *
	 * @param   {String|Number} dmsStr: Degrees or deg/min/sec in variety of formats
	 * @returns {Number} Degrees as decimal number
	 * @throws  {TypeError} dmsStr is an object, perhaps DOM object without .value?
	 */
	static double parseDMS(char* dms);

	/**
	 * Convert decimal degrees to deg/min/sec format
	 *  - degree, prime, double-prime symbols are added, but sign is discarded, though no compass
	 *    direction is added
	 *
	 * @private
	 * @param   {Number} deg: Degrees
	 * @param   {String} [format=dms]: Return value as 'd', 'dm', 'dms'
	 * @param   {Number} [dp=0|2|4]: No of decimal places to use - default 0 for dms, 2 for dm, 4 for d
	 * @returns {String} deg formatted as deg/min/secs according to specified format
	 * @throws  {TypeError} deg is an object, perhaps DOM object without .value?
	 */
	static char* toDMS(double deg, char* format, char* dp);

	/**
	 * Convert numeric degrees to deg/min/sec latitude (suffixed with N/S)
	 *
	 * @param   {Number} deg: Degrees
	 * @param   {String} [format=dms]: Return value as 'd', 'dm', 'dms'
	 * @param   {Number} [dp=0|2|4]: No of decimal places to use - default 0 for dms, 2 for dm, 4 for d
	 * @returns {String} Deg/min/seconds
	 */
	static char* toLat(double deg, char* format, char* dp);

	/**
	 * Convert numeric degrees to deg/min/sec longitude (suffixed with E/W)
	 *
	 * @param   {Number} deg: Degrees
	 * @param   {String} [format=dms]: Return value as 'd', 'dm', 'dms'
	 * @param   {Number} [dp=0|2|4]: No of decimal places to use - default 0 for dms, 2 for dm, 4 for d
	 * @returns {String} Deg/min/seconds
	 */
	static char* toLon(double deg, char* format, char* dp);

	/**
	 * Convert numeric degrees to deg/min/sec as a bearing (0º..360º)
	 *
	 * @param   {Number} deg: Degrees
	 * @param   {String} [format=dms]: Return value as 'd', 'dm', 'dms'
	 * @param   {Number} [dp=0|2|4]: No of decimal places to use - default 0 for dms, 2 for dm, 4 for d
	 * @returns {String} Deg/min/seconds
	 */
	static char* toBrng(double deg, char* format, char* dp);
};

}

#endif /* GEO_H_ */
