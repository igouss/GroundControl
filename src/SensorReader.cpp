#include <stdio.h>    /* Standard input/output definitions */

#include "SensorReader.h"

namespace naxsoft {

SensorReader::SensorReader(naxsoft::Protocol* protocol) :
	protocol(protocol)
{
}

SensorReader::~SensorReader() {
	protocol = NULL;
}


uint32_t SensorReader::readAccelerometer(naxsoft::Protocol* protocol, int16_t& x, int16_t& y, int16_t& z) {
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
//	x = x >> 4;
//	y = y >> 4;
//	z = z >> 4;
	return rz;
}
uint32_t SensorReader::readGyro(naxsoft::Protocol* protocol, int16_t& x, int16_t& y, int16_t& z) {
	uint32_t rz = 0;
	rz += protocol->writeMessageBegin(naxsoft::T_CALL);
	rz += protocol->writeI8(0x7); // 7 = gyroscope
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
//	x = x >> 4;
//	y = y >> 4;
//	z = z >> 4;
	return rz;
}
uint32_t SensorReader::readMagnetometer(naxsoft::Protocol* protocol, int16_t& x, int16_t& y, int16_t& z) {
	uint32_t rz = 0;
	rz += protocol->writeMessageBegin(naxsoft::T_CALL);
	rz += protocol->writeI8(0x6); // 6=magnetometer
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
//	x = x >> 4;
//	y = y >> 4;
//	z = z >> 4;
	return rz;
}

} // namespace
