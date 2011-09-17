#ifndef COMPASS_H_
#define COMPASS_H_

#include <inttypes.h>
#include "vector.h"

namespace naxsoft {

/*
 * This program assumes that the LSM303DLH carrier is oriented with X pointing
 * to the right, Y pointing backward, and Z pointing down (toward the ground).
 * The code compensates for tilts of up to 90 degrees away from horizontal.
 * Vector p should be defined as pointing forward, parallel to the ground,
 * with coordinates {X, Y, Z}.
 */
class Compass {
public:
	Compass();
	virtual ~Compass();

	/**
	 * @param x is the x axis
	 * @param y is the y axis
	 * @param z is the z axis
	 */
	void setAxis(int16_t x, int16_t y, int16_t z);

	/** sets the x, y, and z offset corrections for hard iron calibration
	 *
	 * Calibration details here:
	 *  http://mbed.org/users/shimniok/notebook/quick-and-dirty-3d-compass-calibration/
	 *
	 * If you gather raw magnetometer data and find, for example, x is offset
	 * by hard iron by -20 then pass +20 to this member function to correct
	 * for hard iron.
	 *
	 * @param x is the offset correction for the x axis
	 * @param y is the offset correction for the y axis
	 * @param z is the offset correction for the z axis
	 */
	void setOffset(int16_t x, int16_t y, int16_t z);

	/**
	 * sets the scale factor for the x, y, and z axes
	 *
	 * Calibratio details here:
	 *  http://mbed.org/users/shimniok/notebook/quick-and-dirty-3d-compass-calibration/
	 *
	 * Sensitivity of the three axes is never perfectly identical and this
	 * function can help to correct differences in sensitivity.  You're
	 * supplying a multipler such that x, y and z will be normalized to the
	 * same max/min values
	 */
	void setScale(double x, double y, double z);

	/**
	 *  Returns the number of degrees from the -Y axis that it is pointing.
	 */
	double getHeading(double pitch, double roll);
	double getHeading(const vector *a, const vector *m, const vector *p);

	/**
	 *
	 */
	double getAzimuth();

	double getX();
	double getY();
	double getZ();

private:
	double x;
	double y;
	double z;
	int16_t offset_x;
	int16_t offset_y;
	int16_t offset_z;
	double scale_x;
	double scale_y;
	double scale_z;


	vector p;

	/*
	 * m_max and m_min are calibration values for the maximum and minimum
	 * measurements recorded on each magnetic axis, which can vary for each
	 * LSM303DLH. You should replace the values below with max and min readings from
	 * your particular device.
	 *
	 * To obtain the max and min values, you can use this program's
	 * calibration mode, which is enabled by pressing one of the pushbuttons. While
	 * calibration mode is active, point each of the axes of the LSM303DLH toward
	 * and away from the earth's North Magnetic Pole. Due to space constraints on an
	 * 8x2 LCD, only one axis is displayed at a time; each button selects an axis to
	 * display (top = X, middle = Y, bottom = Z), and pressing any button a second
	 * time exits calibration mode and returns to normal operation.
	 */
	vector m_max;
	vector m_min;
	enum calibration_mode {CAL_NONE, CAL_XYZ};

	// filtering/smoothing
    double x_mu_n;
    double y_mu_n;
    double z_mu_n;
    double x_sigma_sqr_n;
    double y_sigma_sqr_n;
    double z_sigma_sqr_n;



};

}

#endif /* COMPASS_H_ */
