#ifndef SENSORREADER_H_
#define SENSORREADER_H_

#include <stdint.h>   /* Standard types */
#include "thrift/Protocol.h"


namespace naxsoft {

class SensorReader {
public:
	SensorReader(naxsoft::Protocol* protocol);
	virtual ~SensorReader();

	uint32_t readAccelerometer(naxsoft::Protocol* protocol, int16_t& x, int16_t& y, int16_t& z);
	uint32_t readGyro(naxsoft::Protocol* protocol, int16_t& x, int16_t& y, int16_t& z);
	uint32_t readMagnetometer(naxsoft::Protocol* protocol, int16_t& x, int16_t& y, int16_t& z);
private:
	naxsoft::Protocol* protocol;
};

} // namespace

#endif /* SENSORREADER_H_ */
