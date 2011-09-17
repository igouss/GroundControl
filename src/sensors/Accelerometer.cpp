#include <float.h>
#include <math.h>

#include "Accelerometer.h"
#include "Estimator.h"

#define g -9_81 // m/s^2
#define conversion_constant 42

namespace naxsoft {

Accelerometer::Accelerometer() :
	offset_x(0), offset_y(0), offset_z(0), scale_x(1), scale_y(1), scale_z(1),
	x_mu_n(0),
	y_mu_n(0),
	z_mu_n(0),
	x_sigma_sqr_n(DBL_MAX),
	y_sigma_sqr_n(DBL_MAX),
	z_sigma_sqr_n(DBL_MAX)
{
	// TODO Auto-generated constructor stub

}

Accelerometer::~Accelerometer() {
	// TODO Auto-generated destructor stub
}

double Accelerometer::getForceVector() {
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

double Accelerometer::getXangle(double forceVector) {
	return acos(x/forceVector);// * 57.295779513082320876798154814105;
}

double Accelerometer::getYangle(double forceVector) {
	return acos(y/forceVector);// * 57.295779513082320876798154814105;
}

double Accelerometer::Accelerometer::xGravityForce(double angle) {
	return -x * cos(angle);
}
double Accelerometer::yGravityForce(double angle) {
	return -y * cos(angle);
}
double Accelerometer::zGravityForce(double angle) {
	return -z * cos(angle);
}

void Accelerometer::setAxis(int16_t x, int16_t y, int16_t z) {
	this->x = (x + offset_x) * scale_x;
	this->y = (y + offset_y) * scale_y;
	this->z = (z + offset_z) * scale_z;
    Estimator::estimate(this->x, 0.1, &x_mu_n, &x_sigma_sqr_n);
    Estimator::estimate(this->y, 0.1, &y_mu_n, &y_sigma_sqr_n);
    Estimator::estimate(this->z, 0.1, &z_mu_n, &z_sigma_sqr_n);
    this->x = x_mu_n;
    this->y = y_mu_n;
    this->z = z_mu_n;
}

void Accelerometer::setOffset(int16_t x, int16_t y, int16_t z) {
	offset_x = x;
	offset_y = y;
	offset_z = z;
}

void Accelerometer::setScale(double x, double y, double z) {
	scale_x = x;
	scale_y = y;
	scale_z = z;
}

/**
 * the linear vertical (up/down) motion
 * Unit: g-force
 */
double Accelerometer::getSurge(void)
{
	return z;
}

/**
 * the linear lateral (side-to-side) motion
 * Unit: g-force
 */
double Accelerometer::getSway(void)
{
	return x;
}

/**
 * the linear longitudinal (front/back) motion
 * Unit: g-force
 */
double Accelerometer::getHeave(void)
{
	return y;
}
/**
 * the linear vertical (up/down) motion
 * Unit: Metre per second squared
 */
double Accelerometer::getMetricSurge(void)
{
	return z * 9.80665;
}

/**
 * the linear lateral (side-to-side) motion
 * Unit: Metre per second squared
 */
double Accelerometer::getMetricSway(void)
{
	return x * 9.80665;
}

/**
 * the linear longitudinal (front/back) motion
 * Unit: Metre per second squared
 */
double Accelerometer::getMetricHeave(void)
{
	return y * 9.80665;
}


}
