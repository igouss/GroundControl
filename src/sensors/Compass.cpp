#include <math.h>

#include "Compass.h"
#include "Estimator.h"


namespace naxsoft {

Compass::Compass() :
	offset_x(0), offset_y(0), offset_z(0), scale_x(1), scale_y(1), scale_z(1) {
	// TODO Auto-generated constructor stub
}

Compass::~Compass() {
	// TODO Auto-generated destructor stub
}

double Compass::getHeading() {
	return ::atan(y / x); // azimuth
}

void Compass::compensatedTilt(int16_t pitch, int16_t roll) {
	x = x * cos(pitch) + z * sin(pitch);
	y = x * sin(roll) * sin(pitch) + y * cos(roll) - z * sin(roll) * cos(pitch);
}

void Compass::setAxis(double x, double y, double z) {
	this->x = (x + offset_x) * scale_x;
	this->y = (y + offset_y) * scale_y;
	this->z = (z + offset_z) * scale_z;

//    Estimator::estimate(this->x, 0.9, &x_mu_n, &x_sigma_sqr_n);
//    Estimator::estimate(this->y, 0.9, &y_mu_n, &y_sigma_sqr_n);
//    Estimator::estimate(this->z, 0.9, &z_mu_n, &z_sigma_sqr_n);
//    this->x = x_mu_n;
//    this->y = y_mu_n;
//    this->z = z_mu_n;
}

void Compass::setOffset(double x, double y, double z) {
	offset_x = x;
	offset_y = y;
	offset_z = z;
}

void Compass::setScale(double x, double y, double z) {
	scale_x = x;
	scale_y = y;
	scale_z = z;
}

void Compass::calibrate() {
	// set magnetometer max and min:
	if (x > max_x) max_x = x;
	if (x < min_x) min_x = x;

	if (y > max_y) max_y = y;
	if (y < min_y) min_y = y;

	if (z > max_z) max_z = z;
	if (z < min_z) min_z = z;
}

}
