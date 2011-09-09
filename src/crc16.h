#ifndef CRC16_H_
#define CRC16_H_

uint8_t lo8(uint16_t val) {
	return (uint8_t) val;
}

uint8_t hi8(uint16_t val) {
	return (uint8_t) (val >> 8);
}


uint16_t crc_ccitt_update(uint16_t crc, uint8_t data) {
	data ^= lo8(crc);
	data ^= data << 4;

	return ((((uint16_t) data << 8) | hi8(crc)) ^ (uint8_t) (data >> 4)
			^ ((uint16_t) data << 3));
}

#endif /* CRC16_H_ */
