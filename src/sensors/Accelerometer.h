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
    void setAxis(double x, double y, double z);

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
    void setOffset(double x, double y, double z);

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

	double maxAcceleration();
	double xGravityForce(double angle);
	double yGravityForce(double angle);
	double zGravityForce(double angle);

	/**
	 * the linear vertical (up/down) motion
	 */
	int getSurge(void)
	{
		return x;
	}

	/**
	 * the linear lateral (side-to-side) motion
	 */
	int getSway(void)
	{
		return y;
	}

	/**
	 * the linear longitudinal (front/back) motion
	 */
	int getHeave(void)
	{
		return z;
	}



	void calibrate();
private:
    double x;
    double y;
    double z;

    double offset_x;
    double offset_y;
    double offset_z;
    double scale_x;
    double scale_y;
    double scale_z;

	// calibration
	double max_x;
	double max_y;
	double max_z;
	double min_x;
	double min_y;
	double min_z;

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
