#include <math.h>

#include "Compass.h"
#include "Estimator.h"

namespace naxsoft {

Compass::Compass() :
	offset_x(0), offset_y(0), offset_z(0), scale_x(1), scale_y(1), scale_z(1) {

	p.x = 0;
	p.y = -1;
	p.z = 0;

	m_max.x = 340;
	m_max.y = 517;
	m_max.z = 416;
	m_min.x = -624;
	m_min.x = -496;
	m_min.x = -462;

}

Compass::~Compass() {
}

/**
 * Transform X, Y, and Z magnetic readings to the horizontal plane (X_H, Y_H)
 */
double Compass::getHeading(double roll, double pitch) {
	double MAG_X, MAG_Y;
	double MAG_Heading = 0;

	double cos_roll = cos(roll);
	double sin_roll = sin(roll);
	double cos_pitch = cos(pitch);
	double sin_pitch = sin(pitch);

	// Tilt compensated Magnetic filed X:
	MAG_X = x * cos_pitch + y * sin_roll * sin_pitch + z * cos_roll * sin_pitch;
	// Tilt compensated Magnetic filed Y:
	MAG_Y = y * cos_roll - z * sin_roll;
	// Magnetic Heading
	MAG_Heading = atan2(-MAG_Y, MAG_X);
	return MAG_Heading;
}

/**
 * Returns a heading (in degrees) given an acceleration vector a due to gravity,
 * a magnetic vector m, and a facing vector p.
 */
double Compass::getHeading(const vector *a, const vector *m, const vector *p) {
	vector E;
	vector N;

	// cross magnetic vector (magnetic north + inclination) with "down" (acceleration vector) to produce "east"
	Vector::cross(m, a, &E);
	Vector::normalize(&E);

	// cross "down" with "east" to produce "north" (parallel to the ground)
	Vector::cross(a, &E, &N);
	Vector::normalize(&N);

	// compute heading
	double heading = round(atan2(Vector::dot(&E, p), Vector::dot(&N, p)) * 180 / M_PI);
	if (heading < 0) {
		heading += 360;
	}
	return heading;
}

/**
 * Assuming that the compass lies perfectly horizontal, the heading can be computed this way:
 *  (y>0) heading = 90 - atan2(x,y)*180 / pi
 *  (y<0) heading = 270 - atan2(x,y)*180 / pi
 *  (y=0, x<0) heading = 180.0
 *  (y=0, x>0) heading = 0.0
 *
 */
double Compass::getAzimuth() {
    if (y>0) { return 90 - atan2(x,y)*180 / M_PI; }
    if (y<0) { return 270 - atan2(x,y)*180 / M_PI; }
    if (y=0, x<0) { return 180.0; }
    if (y=0, x>0) { return 0.0; }


//	if (x == 0 && y <= 0) {
//		return 90.0;
//	} else if (x == 0 && y > 0) {
//		return 270.0;
//	} else if (x < 0) {
//		return 180 - (atan(y / x)) * 180 / M_PI;
//	} else if (x > 0 && y <= 0) {
//		return -(atan(y / x)) * 180 / M_PI;
//	} else { // (x > 0 && y > 0) {
//		return 360 - (atan(y / x)) * 180 / M_PI;
//	}
}

void Compass::setAxis(int16_t x, int16_t y, int16_t z) {
//	this->x = (x + offset_x) * scale_x;
//	this->y = (y + offset_y) * scale_y;
//	this->z = (z + offset_z) * scale_z;


	// shift and scale
	this->x = (x - m_min.x) / (m_max.x - m_min.x) * 2 - 1.0;
	this->y = (y - m_min.y) / (m_max.y - m_min.y) * 2 - 1.0;
	this->z = (z - m_min.z) / (m_max.z - m_min.z) * 2 - 1.0;


	//    Estimator::estimate(this->x, 0.9, &x_mu_n, &x_sigma_sqr_n);
	//    Estimator::estimate(this->y, 0.9, &y_mu_n, &y_sigma_sqr_n);
	//    Estimator::estimate(this->z, 0.9, &z_mu_n, &z_sigma_sqr_n);
	//    this->x = x_mu_n;
	//    this->y = y_mu_n;
	//    this->z = z_mu_n;
}

double Compass::getX() {
	return x;
}
double Compass::getY() {
	return y;
}
double Compass::getZ() {
	return z;
}

void Compass::setOffset(int16_t x, int16_t y, int16_t z) {
	offset_x = x;
	offset_y = y;
	offset_z = z;
}

void Compass::setScale(double x, double y, double z) {
	scale_x = x;
	scale_y = y;
	scale_z = z;
}

}
