#ifndef DATALOGGER_H_
#define DATALOGGER_H_

#include <stdint.h>   /* Standard types */

namespace naxsoft {

class DataLogger {
public:
	DataLogger();
	virtual ~DataLogger();

	void log(int16_t mx, int16_t my, int16_t mz, int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz, int i);
};

} // namespace

#endif /* DATALOGGER_H_ */

