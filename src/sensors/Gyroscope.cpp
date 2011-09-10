#include <math.h>

#include "Gyroscope.h"
#include "Estimator.h"


namespace naxsoft {

Gyroscope::Gyroscope() :
	offset_x(0), offset_y(0), offset_z(0), scale_x(1), scale_y(1), scale_z(1) {
}

Gyroscope::~Gyroscope() {
}

double Gyroscope::getPitch() {
	return x;
}
double Gyroscope::getYaw() {
	return y;
}
double Gyroscope::getRoll() {
	return z;
}


double Gyroscope::maxAcceleration() {
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void Gyroscope::setAxis(double x, double y, double z) {
	this->x = (x + offset_x) * scale_x;
	this->y = (y + offset_y) * scale_y;
	this->z = (z + offset_z) * scale_z;

//    Estimator::estimate(this->x, 0.1, &x_mu_n, &x_sigma_sqr_n);
//    Estimator::estimate(this->y, 0.1, &y_mu_n, &y_sigma_sqr_n);
//    Estimator::estimate(this->z, 0.1, &z_mu_n, &z_sigma_sqr_n);
//    this->x = x_mu_n;
//    this->y = y_mu_n;
//    this->z = z_mu_n;

}

void Gyroscope::setOffset(double x, double y, double z) {
	offset_x = x;
	offset_y = y;
	offset_z = z;
}

void Gyroscope::setScale(double x, double y, double z) {
	scale_x = x;
	scale_y = y;
	scale_z = z;
}

void Gyroscope::calibrate() {
	// set magnetometer max and min:
	if (x > max_x) max_x = x;
	if (x < min_x) min_x = x;

	if (y > max_y) max_y = y;
	if (y < min_y) min_y = y;

	if (z > max_z) max_z = z;
	if (z < min_z) min_z = z;
}

}
