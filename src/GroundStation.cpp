/*
 * Arduino-serial
 * --------------
 *
 * A simple command-line example program showing how a computer can
 * communicate with an Arduino board. Works on any POSIX system (Mac/Unix/PC)
 *
 *
 * Compile with something like:
 * gcc -o arduino-serial arduino-serial.c
 *
 * Created 5 December 2006
 * Copyleft (c) 2006, Tod E. Kurt, tod@todbot.com
 * http://todbot.com/blog/
 *
 *
 * Updated 8 December 2006:
 *  Justin McBride discoevered B14400 & B28800 aren't in Linux's termios.h.
 *  I've included his patch, but commented out for now.  One really needs a
 *  real make system when doing cross-platform C and I wanted to avoid that
 *  for this little program. Those baudrates aren't used much anyway. :)
 *
 * Updated 26 December 2007:
 *  Added ability to specify a delay (so you can wait for Arduino Diecimila)
 *  Added ability to send a binary byte number
 *
 * Update 31 August 2008:
 *  Added patch to clean up odd baudrates from Andy at hexapodia.org
 *
 */

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

#include "thrift/Protocol.h"
#include "thrift/SerialTransport.h"

#include "SensorReader.h"
#include "DataLogger.h"
#include "LatLon.h"



int main(int argc, char *argv[]) {

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

	if(!transport.isOpen()) {
		exit(EXIT_FAILURE);
	}

	naxsoft::Protocol protocol(&transport);
	naxsoft::SensorReader* sensorReader = new naxsoft::SensorReader(&protocol);
	naxsoft::DataLogger* dataLogger = new naxsoft::DataLogger();

	int16_t mx, my, mz = 0;
	int16_t ax, ay, az = 0;
	int16_t gx, gy, gz = 0;

	uint32_t rz = 0;

	int i = 0;
	while(true) {
		rz = sensorReader->readAccelerometer(&protocol, ax, ay, az);
		rz = sensorReader->readGyro(&protocol, gx, gy, gz);
		rz = sensorReader->readMagnetometer(&protocol, mx, my, mz);
		dataLogger->log(mx, my, mz, ax, ay, az, gx, gy, gz, i);
		i++;
	}
	exit(EXIT_SUCCESS);
} // end main
