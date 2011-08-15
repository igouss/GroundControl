#include "Geo.h"

namespace naxsoft {

double Geo::parseDMS(char* dms) {
	//  // strip off any sign or compass dir'n & split out separate d/m/s
	//  var dms = String(dmsStr).trim().replace(/^-/,'').replace(/[NSEW]$/i,'').split(/[^0-9.,]+/);
	//  if (dms[dms.length-1]=='') dms.splice(dms.length-1);  // from trailing symbol
	//
	//  if (dms == '') return NaN;
	//
	//  // and convert to decimal degrees...
	//  switch (dms.length) {
	//    case 3:  // interpret 3-part result as d/m/s
	//      var deg = dms[0]/1 + dms[1]/60 + dms[2]/3600;
	//      break;
	//    case 2:  // interpret 2-part result as d/m
	//      var deg = dms[0]/1 + dms[1]/60;
	//      break;
	//    case 1:  // just d (possibly decimal) or non-separated dddmmss
	//      var deg = dms[0];
	//      // check for fixed-width unseparated format eg 0033709W
	//      //if (/[NS]/i.test(dmsStr)) deg = '0' + deg;  // - normalise N/S to 3-digit degrees
	//      //if (/[0-9]{7}/.test(deg)) deg = deg.slice(0,3)/1 + deg.slice(3,5)/60 + deg.slice(5)/3600;
	//      break;
	//    default:
	//      return NaN;
	//  }
	//  if (/^-|[WS]$/i.test(dmsStr.trim())) deg = -deg; // take '-', west and south as -ve
	//  return Number(deg);
	return 0;
}
char* Geo::toDMS(double deg, char* format, char* dp) {
	//  if (typeof deg == 'object') throw new TypeError('Geo.toDMS - deg is [DOM?] object');
	//  if (isNaN(deg)) return 'NaN';  // give up here if we can't make a number from deg
	//
	//    // default values
	//  if (typeof format == 'undefined') format = 'dms';
	//  if (typeof dp == 'undefined') {
	//    switch (format) {
	//      case 'd': dp = 4; break;
	//      case 'dm': dp = 2; break;
	//      case 'dms': dp = 0; break;
	//      default: format = 'dms'; dp = 0;  // be forgiving on invalid format
	//    }
	//  }
	//
	//  deg = Math.abs(deg);  // (unsigned result ready for appending compass dir'n)
	//
	//  switch (format) {
	//    case 'd':
	//      d = deg.toFixed(dp);     // round degrees
	//      if (d<100) d = '0' + d;  // pad with leading zeros
	//      if (d<10) d = '0' + d;
	//      dms = d + '\u00B0';      // add º symbol
	//      break;
	//    case 'dm':
	//      var min = (deg*60).toFixed(dp);  // convert degrees to minutes & round
	//      var d = Math.floor(min / 60);    // get component deg/min
	//      var m = (min % 60).toFixed(dp);  // pad with trailing zeros
	//      if (d<100) d = '0' + d;          // pad with leading zeros
	//      if (d<10) d = '0' + d;
	//      if (m<10) m = '0' + m;
	//      dms = d + '\u00B0' + m + '\u2032';  // add º, ' symbols
	//      break;
	//    case 'dms':
	//      var sec = (deg*3600).toFixed(dp);  // convert degrees to seconds & round
	//      var d = Math.floor(sec / 3600);    // get component deg/min/sec
	//      var m = Math.floor(sec/60) % 60;
	//      var s = (sec % 60).toFixed(dp);    // pad with trailing zeros
	//      if (d<100) d = '0' + d;            // pad with leading zeros
	//      if (d<10) d = '0' + d;
	//      if (m<10) m = '0' + m;
	//      if (s<10) s = '0' + s;
	//      dms = d + '\u00B0' + m + '\u2032' + s + '\u2033';  // add º, ', " symbols
	//      break;
	//  }
	//
	//  return dms;

	return 0;
}
char* Geo::toLat(double deg, char* format, char* dp) {
	//  var lat = Geo.toDMS(deg, format, dp);
	//  return lat=='' ? '' : lat.slice(1) + (deg<0 ? 'S' : 'N');  // knock off initial '0' for lat!

	return 0;
}
char* Geo::toLon(double deg, char* format, char* dp) {
	//  var lon = Geo.toDMS(deg, format, dp);
	//  return lon=='' ? '' : lon + (deg<0 ? 'W' : 'E');

	return 0;
}
char* Geo::toBrng(double deg, char* format, char* dp) {
	//  deg = (Number(deg)+360) % 360;  // normalise -ve values to 180º..360º
	//  var brng =  Geo.toDMS(deg, format, dp);
	//  return brng.replace('360', '0');  // just in case rounding took us up to 360º!
	return 0;
}



}
