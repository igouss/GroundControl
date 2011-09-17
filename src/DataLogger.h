#ifndef DATALOGGER_H_
#define DATALOGGER_H_

#include <stdint.h>   /* Standard types */

namespace naxsoft {

class DataLogger {
public:
	DataLogger();
	virtual ~DataLogger();

	void log(double mx, double my, double mz, double ax, double ay, double az, double gx, double gy, double gz, int i);
};

} // namespace

#endif /* DATALOGGER_H_ */

