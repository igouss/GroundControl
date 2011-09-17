#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_
#include <stdint.h>   /* Standard types */

namespace naxsoft {

class Accelerometer {
public:
	Accelerometer();
	virtual ~Accelerometer();

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

	double getForceVector();
	double getXangle(double forceVector);
	double getYangle(double forceVector);


	double xGravityForce(double angle);
	double yGravityForce(double angle);
	double zGravityForce(double angle);

	/**
	 * the linear vertical (up/down) motion
	 * Unit: g-force
	 */
	double getSurge(void);

	/**
	 * the linear lateral (side-to-side) motion
	 * Unit: g-force
	 */
	double getSway(void);

	/**
	 * the linear longitudinal (front/back) motion
	 * Unit: g-force
	 */
	double getHeave(void);

	/**
	 * the linear vertical (up/down) motion
     * Unit: Metre per second squared
	 */
	double getMetricSurge(void);

	/**
	 * the linear lateral (side-to-side) motion
     * Unit: Metre per second squared
	 */
	double getMetricSway(void);

	/**
	 * the linear longitudinal (front/back) motion
     * Unit: Metre per second squared
	 */
	double getMetricHeave(void);

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

	// filtering/smoothing
    double x_mu_n;
    double y_mu_n;
    double z_mu_n;
    double x_sigma_sqr_n;
    double y_sigma_sqr_n;
    double z_sigma_sqr_n;

};

}

#endif /* ACCELEROMETER_H_ */
