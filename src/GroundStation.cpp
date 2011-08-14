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


uint32_t readAccelerometer(naxsoft::Protocol* protocol, int16_t& x, int16_t& y, int16_t& z) {
	uint32_t rz = 0;
	rz += protocol->writeMessageBegin(naxsoft::T_CALL);
	rz += protocol->writeI8(0x5); // ACCELE;
	rz += protocol->writeMessageEnd();

	enum naxsoft::TMessageType messageType;

	rz += protocol->readMessageBegin(messageType);

	if(!naxsoft::T_REPLY) {
		printf("Wrong reply type %d", messageType);
		x = -1;
		y = -1;
		z = -1;
	} else {
		rz += protocol->readI16(x);
		rz += protocol->readI16(y);
		rz += protocol->readI16(z);
		rz += protocol->readMessageEnd();
	}
	return rz;
}

int main(int argc, char *argv[]) {
	naxsoft::SerialTransport transport("/dev/cu.usbserial-A70041iS", B9600);
	transport.open();

	if(!transport.isOpen()) {
		exit(EXIT_FAILURE);
	}

	naxsoft::Protocol protocol(&transport);

	int16_t x, y, z = 0;

	uint32_t rz = 0;
	for(int i =0; i<500; i++) {
		rz = readAccelerometer(&protocol, x, y, z);
		printf("[%d][%d] accelerometer %d %d %d\n", i, rz, x, y, z);
	}
	exit(EXIT_SUCCESS);
} // end main



