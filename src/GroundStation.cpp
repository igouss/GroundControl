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

#include <QtGui>
#include <QApplication>

#include "ui/GroundControlWindow.h"
#include "ui/SensorThread.h"




int main(int argc, char *argv[]) {
//	(void) argc; // silent unused args warning
//	(void) argv; // silent unused args warning

	// To show logging in real-time, disable output buffering.
	setbuf(stdout, NULL);

	int status;
	QApplication app(argc, argv);
    naxsoft::AddressBook addressBook;
    naxsoft::SensorThread sensorThread;

    QObject::connect(&sensorThread, SIGNAL(updateAzimuth(qreal)), addressBook.compassWidget, SLOT(setAzimuth(qreal)));

    sensorThread.start();
    addressBook.show();
    status = app.exec();

    sensorThread.exit();

    exit(status);

//	exit(EXIT_SUCCESS);
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


