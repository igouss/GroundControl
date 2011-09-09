#include <iostream>
#include <streambuf>

#include <locale>
#include <cstdio>

#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h>
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <sys/ioctl.h>

#include "SerialTransport.h"

namespace naxsoft {

SerialTransport::SerialTransport(const char serialport[256], speed_t baudrate = B9600)
{
	this->baudrate = baudrate;
	this->serialport = serialport,
	this->fd = 0;
}


SerialTransport::~SerialTransport() {
	close();
}


void SerialTransport::open(void) {
	fd = serialport_init(serialport, baudrate);
	this->outStream = new boost::FdOStream(fd);
	this->inStream = new boost::FdIStream(fd);

}

void SerialTransport::close(void) {
	if(fd != 0) {
		// ::close(fd);

		// The file descriptor will be automatically closed when the stdio_filebuf is closed/destroyed.
		delete outStream;
		delete inStream;
		fd = 0;
	}
}

bool SerialTransport::isOpen(void) const {
	return fd > 0;
}

void SerialTransport::flush() const {
	outStream->flush();
}

bool SerialTransport::peek() const {
	if(!inStream->good() || inStream->eof()) {
		inStream->clear();
	}
	return inStream->peek();
}

int32_t SerialTransport::read(uint8_t* buf, uint32_t len) const {
	// basically readAll will busy-wait
	// if last time we tried to read and failed to read data from the wire.
	if(!inStream->good() || inStream->eof()) {
		inStream->clear();
		return 0;
	}

	inStream->read((char*) buf, len); // todo unblocking call
	len = inStream->gcount();
	return len;
}

void SerialTransport::write(const uint8_t* buf, uint32_t len) const {
	outStream->write((char*) buf, len);
}

int32_t SerialTransport::readAll(uint8_t* buf, uint32_t len) const {
	uint32_t have = 0;
	int32_t get = 0;

	uint8_t tryCount = 0;

	while (have < len) {
		get = read(buf + have, len - have);
		if(get == 0) {
			usleep(10000);
			if(++tryCount == 255) {
				return -1;
			}
		}
//		if(get < 0) {
//		}
		have += get;
	}

	return have;
}

// takes the string name of the serial port (e.g. "/dev/tty.usbserial","COM1")
// and a baud rate (bps) and connects to that port at that speed and 8N1.
// opens the port in fully raw mode so you can send binary data.
// returns valid fd, or -1 on error
int SerialTransport::serialport_init(const char* serialport, int baud) {
	struct termios toptions;
	int fd;

	//fprintf(stderr,"init_serialport: opening port %s @ %d bps\n",
	//        serialport,baud);

	fd = ::open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);

	if (fd == -1) {
		perror("init_serialport: Unable to open port ");
		return -1;
	}

	/*
	 * Get the attribues associated with the serial port
	 * See: http://www.opengroup.org/onlinepubs/009695399/functions/tcgetattr.html
	 */
	if (tcgetattr(fd, &toptions) < 0) {
		perror("init_serialport: Couldn't get term attributes");
		::close(fd);
		fd = 0;
		return -1;
	}
	speed_t brate = baud; // let you override switch below if needed
	switch (baud) {
	case 4800:
		brate = B4800;
		break;
	case 9600:
		brate = B9600;
		break;
#ifdef B14400
	case 14400:
		brate = B14400;
		break;
#endif
	case 19200:
		brate = B19200;
		break;
#ifdef B28800
	case 28800:
		brate = B28800;
		break;
#endif
	case 38400:
		brate = B38400;
		break;
	case 57600:
		brate = B57600;
		break;
	case 115200:
		brate = B115200;
		break;
	}
	cfsetispeed(&toptions, brate);
	cfsetospeed(&toptions, brate);


	/*
	 * See: http://linux.die.net/man/3/cfmakeraw
	 * And: http://www.gnu.org/s/libc/manual/html_node/Noncanonical-Input.html
	 */

	// 8N1
	toptions.c_cflag &= ~PARENB;
	toptions.c_cflag &= ~CSTOPB;
	toptions.c_cflag &= ~CSIZE;
	toptions.c_cflag |= CS8;
	// no flow control
	toptions.c_cflag &= ~CRTSCTS;

	toptions.c_cflag |= CREAD | CLOCAL; // turn on READ & ignore ctrl lines
	toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl

	toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
	toptions.c_oflag &= ~OPOST; // make raw

	// see: http://unixwiz.net/techtips/termios-vmin-vtime.html
	toptions.c_cc[VMIN] = 0; // specifies the minimum number of bytes that must be available in the input queue in order for read to return.
	toptions.c_cc[VTIME] = 20; // specifies how long to wait for input before returning, in units of 0.1 seconds.


	/*
	 * Apply the changes to the serial port.
	 * See: http://www.delorie.com/gnu/docs/glibc/libc_360.html
	 *
	 * TCSAFLUSH tells the underlying OS to wait until the all queued output has been written,
	 * and to discard any queued input
	 */
	if (tcsetattr(fd, TCSANOW, &toptions) < 0) {
		perror("init_serialport: Couldn't set term attributes");
		return -1;
	}
	return fd;
}
} // namespace
