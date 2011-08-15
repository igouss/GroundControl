#include "Calibrator.h"

namespace naxsoft {

Calibrator::Calibrator() {
	// TODO Auto-generated constructor stub

}

Calibrator::~Calibrator() {
	// TODO Auto-generated destructor stub
}

void Calibrator::calibrateAccelerometer() {
	double xAxisLinearAccelerometerSensetivity = 0;
	double yAxisLinearAccelerometerSensetivity = 0;
	double zAxisLinearAccelerometerSensetivity = 0;

	double xUp, xDown, yUp, yDown, zUp, zDown = 0;

//	Sensor::readAccelerometerXAxisPointingUp(xUp);
//	Sensor::readAccelerometerXAxisPointingDown(xDown);
//	Sensor::readAccelerometerXAxisPointingUp(yUp);
//	Sensor::readAccelerometerXAxisPointingDown(yDown);
//	Sensor::readAccelerometerXAxisPointingUp(zUp);
//	Sensor::readAccelerometerXAxisPointingDown(zDown);

	// calibrate x axis
	if(xUp > xDown) {
		xAxisLinearAccelerometerSensetivity = (xUp - xDown) / 2;
	} else {
		xAxisLinearAccelerometerSensetivity = (xDown - xUp) / 2;
	}

	// calibrate y axis
	if(yUp > yDown) {
		yAxisLinearAccelerometerSensetivity = (yUp - yDown) / 2;
	} else {
		yAxisLinearAccelerometerSensetivity = (yDown - yUp) / 2;
	}

	// calibrate z axis
	if(zUp > zDown) {
		zAxisLinearAccelerometerSensetivity = (zUp - zDown) / 2;
	} else {
		zAxisLinearAccelerometerSensetivity = (zDown - zUp) / 2;
	}

}
}
