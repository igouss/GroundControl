#ifndef GYROSCOPE_H_
#define GYROSCOPE_H_

#include <stdint.h>   /* Standard types */

namespace naxsoft {


/**
 *              +z yaw
 *               |
 *               |      +y roll
 *               |     /
 *               |----/----
 *              /| NOKIA  /|
 *             //|--/--- / |
 *            // | /   //  /
 *           //  |/   //  /
 *          //   '--------------- +x pitch
 *         //       //  /
 *        //       //  /
 *       /---------/  /
 *      /    O    /  /
 *     /         /  /
 *     ----------  /
 *     |_________!/
 *
 */

class Gyroscope {
public:
	Gyroscope();
	virtual ~Gyroscope();

	/**
	 * @param x is the x axis
	 * @param y is the y axis
	 * @param z is the z axis
	 */
	void setAxis(int16_t x, int16_t y, int16_t z);

	/** sets the x, y, and z offset corrections
	 *
	 * @param x is the offset correction for the x axis
	 * @param y is the offset correction for the y axis
	 * @param z is the offset correction for the z axis
	 */
	void setOffset(double x, double y, double z);

	/**
	 * sets the scale factor for the x, y, and z axes
	 */
	void setScale(double x, double y, double z);

	double maxAcceleration();

	double getPitch();
	double getYaw();
	double getRoll();

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

#endif /* GYROSCOPE_H_ */
