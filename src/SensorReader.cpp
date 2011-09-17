#include <stdio.h>    /* Standard input/output definitions */

#include "SensorReader.h"
#include "crc16.h"

namespace naxsoft {

SensorReader::SensorReader(naxsoft::Protocol* protocol) :
	protocol(protocol) {
}

SensorReader::~SensorReader() {
	protocol = NULL;
}

uint32_t SensorReader::readAccelerometer(int16_t& x, int16_t& y, int16_t& z) {
	uint32_t rz = 0;
	uint16_t localcrc = 0xffff;
	int16_t remotecrc = 0x0000;

	uint16_t requestSeqId = protocol->getNextSeqId();
	uint16_t replySeqId = requestSeqId = 0;

	rz += protocol->writeMessageBegin(naxsoft::T_CALL, requestSeqId);
	rz += protocol->writeI8(0x5); // ACCELE;
	rz += protocol->writeMessageEnd();

	enum naxsoft::TMessageType messageType;

	rz += protocol->readMessageBegin(messageType, requestSeqId);
	bool isValidSeq = (requestSeqId == replySeqId);

	if (naxsoft::T_REPLY == messageType && isValidSeq) {
		rz += protocol->readI16(x);
		localcrc = crc_ccitt_update(localcrc, hi8(x));
		localcrc = crc_ccitt_update(localcrc, lo8(x));

		rz += protocol->readI16(y);
		localcrc = crc_ccitt_update(localcrc, hi8(y));
		localcrc = crc_ccitt_update(localcrc, lo8(y));

		rz += protocol->readI16(z);
		localcrc = crc_ccitt_update(localcrc, hi8(z));
		localcrc = crc_ccitt_update(localcrc, lo8(z));

		rz += protocol->readI16(remotecrc);
		rz += protocol->readMessageEnd();
	}

	if (localcrc != (uint16_t) remotecrc || !isValidSeq) {
		return 0;
	} else {
		return rz;
	}
}
uint32_t SensorReader::readGyro(int16_t& x, int16_t& y, int16_t& z) {
	uint32_t rz = 0;
	uint16_t localcrc = 0xffff;
	int16_t remotecrc = 0x0000;

	uint16_t requestSeqId = protocol->getNextSeqId();
	uint16_t replySeqId = requestSeqId = 0;

	rz += protocol->writeMessageBegin(naxsoft::T_CALL, requestSeqId);
	rz += protocol->writeI8(0x7); // 7 = gyroscope
	rz += protocol->writeMessageEnd();

	enum naxsoft::TMessageType messageType;

	rz += protocol->readMessageBegin(messageType, replySeqId);
	bool isValidSeq = (requestSeqId == replySeqId);

	if (naxsoft::T_REPLY == messageType && isValidSeq) {
		rz += protocol->readI16(x);
		localcrc = crc_ccitt_update(localcrc, hi8(x));
		localcrc = crc_ccitt_update(localcrc, lo8(x));

		rz += protocol->readI16(y);
		localcrc = crc_ccitt_update(localcrc, hi8(y));
		localcrc = crc_ccitt_update(localcrc, lo8(y));

		rz += protocol->readI16(z);
		localcrc = crc_ccitt_update(localcrc, hi8(z));
		localcrc = crc_ccitt_update(localcrc, lo8(z));

		rz += protocol->readI16(remotecrc);

		rz += protocol->readMessageEnd();
	}

	if (localcrc != (uint16_t) remotecrc || !isValidSeq) {
		return 0;
	} else {
		return rz;
	}
}
uint32_t SensorReader::readMagnetometer(int16_t& x, int16_t& y, int16_t& z) {
	uint32_t rz = 0;
	uint16_t localcrc = 0xffff;
	int16_t remotecrc = 0x0000;

	uint16_t requestSeqId = protocol->getNextSeqId();
	uint16_t replySeqId = requestSeqId = 0;

	rz += protocol->writeMessageBegin(naxsoft::T_CALL, requestSeqId);
	rz += protocol->writeI8(0x6); // 6=magnetometer
	rz += protocol->writeMessageEnd();

	enum naxsoft::TMessageType messageType;

	rz += protocol->readMessageBegin(messageType, replySeqId);

	bool isValidSeq = (requestSeqId == replySeqId);

	if (naxsoft::T_REPLY == messageType && isValidSeq) {
		rz += protocol->readI16(x);
		localcrc = crc_ccitt_update(localcrc, hi8(x));
		localcrc = crc_ccitt_update(localcrc, lo8(x));

		rz += protocol->readI16(y);
		localcrc = crc_ccitt_update(localcrc, hi8(y));
		localcrc = crc_ccitt_update(localcrc, lo8(y));

		rz += protocol->readI16(z);
		localcrc = crc_ccitt_update(localcrc, hi8(z));
		localcrc = crc_ccitt_update(localcrc, lo8(z));

		rz += protocol->readI16(remotecrc);

		rz += protocol->readMessageEnd();
	}

	if (localcrc != (uint16_t) remotecrc || !isValidSeq) {
		return 0;
	} else {
		return rz;
	}
}

} // namespace
