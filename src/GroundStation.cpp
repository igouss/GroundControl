#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h>
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>
#include <math.h>

#include "thrift/Protocol.h"
#include "thrift/SerialTransport.h"

#include "sensors/Compass.h"
#include "sensors/Accelerometer.h"
#include "sensors/Gyroscope.h"

#include "SensorReader.h"
#include "DataLogger.h"
#include "LatLon.h"


naxsoft::Compass compass;
naxsoft::Accelerometer accelerometer;
naxsoft::Gyroscope gyro;

int main(int argc, char *argv[]) {
	// To show logging in real-time, disable output buffering.
	setbuf(stdout, NULL);

	//	naxsoft::Compass* compass = new naxsoft::Compass;


	// 966.9 km										50° 3' 59.0004"   -5° 32' 3.0012"    58° 38' 38.0004"    -3° 4' 11.9994"
	// printf("Distance %fkm\n", naxsoft::LatLon::calcDistance(50.06638888888889, -5.534166666666667, 58.64388888888889, -3.0700000000000003));
	// 9.1175°									50° 3' 51.0006"     -5° 42' 52.9992"      58° 38' 38.0004"	-3° 4' 11.9994"
	// printf("Bearing %f°\n", naxsoft::LatLon::getBearing(50.064166666666665, -5.714722222222222, 58.64388888888889, -3.0700000000000003));


	//	double decimalDegrees  = 50.064166666666665;
	//	naxsoft::dmsData dms;
	//	naxsoft::LatLon::decimalDegreesToDMS(decimalDegrees, &dms);
	//	printf("Decimal %f Equals Sexagesimal %d° %ld' %f\"\n", decimalDegrees, dms.degree, dms.min, dms.sec);

	naxsoft::SerialTransport transport("/dev/cu.usbserial-A70041iS", B9600);
	transport.open();

	if (!transport.isOpen()) {
		exit(EXIT_FAILURE);
	}

	naxsoft::Protocol protocol(&transport);
	naxsoft::SensorReader* sensorReader = new naxsoft::SensorReader(&protocol);
	naxsoft::DataLogger* dataLogger = new naxsoft::DataLogger();

	int16_t mx, my, mz = 0;
	int16_t ax, ay, az = 0;
	int16_t gx, gy, gz = 0;

	uint32_t rz = 0;

//	accelerometer.setScale(18.0 / 256.0, 18.0 / 256.0, 18.0 / 256.0);
	accelerometer.setOffset(14, 21, -2);

	int i = 0;

	while (true) {
		do {
			rz = sensorReader->readAccelerometer(ax, ay, az);
			accelerometer.setAxis(ax, ay, az);
			accelerometer.calibrate();
		} while (rz == 0);
		do {
			rz = sensorReader->readGyro(gx, gy, gz);
			gyro.setAxis(gx, gy, gz);
			gyro.calibrate();
		} while (rz == 0);
		do {
			rz = sensorReader->readMagnetometer(mx, my, mz);
			compass.setAxis(mx, my, mz);
			compass.calibrate();
		} while (rz == 0);

		double r = accelerometer.getForceVector();
		double accXangle = naxsoft::LatLon::radToDegrees(accelerometer.getXangle(r)); // when flat x & y are 90 deg to z
		double accYangle = naxsoft::LatLon::radToDegrees(accelerometer.getYangle(r));

		dataLogger->log(accXangle, accYangle, 0, accelerometer.getSurge(), accelerometer.getSway(), accelerometer.getHeave(), 0, 0, 0, i);
//		dataLogger->log(mx, my, mz, accelerometer.getSurge(), accelerometer.getSway(), accelerometer.getHeave(), gyro.getPitch(), gyro.getYaw(), gyro.getRoll(), i);

		//		printf("maxAcceleration = %f\n", accelerometer.maxAcceleration());

		i++;
	}
	exit(EXIT_SUCCESS);
} // end main

//void calibrateAccelerometer(naxsoft::SensorReader* sensorReader) {
//	int16_t sampleX[100];
//	int16_t sampleY[100];
//	int16_t sampleZ[100];
//	uint32_t rz = 0;
//
//	for(int i = 0; i < 100; i++) {
//		do {
//			rz = sensorReader->readAccelerometer(sampleX[i], sampleY[i], sampleZ[i]);
//		} while (rz == 0);
//	}
//}


