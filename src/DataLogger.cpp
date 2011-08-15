#include <stdio.h>    /* Standard input/output definitions */

#include "DataLogger.h"

namespace naxsoft {

DataLogger::DataLogger() {
	printf("mx\tmy\tmz\tax\tay\taz\tgx\tgy\tgz\tms\n");
}

DataLogger::~DataLogger() {
	// TODO Auto-generated destructor stub
}

void DataLogger::log(int16_t mx, int16_t my, int16_t mz, int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz, int i) {
	printf("%04d\t%04d\t%04d\t%04d\t%04d\t%04d\t%05d\t%05d\t%05d\t%d\n", mx, my, mz, ax, ay, az, gx, gy, gz, i);

//	printf("0:%04d\n", mx);
//	printf("1:%04d\n", my);
//	printf("2:%04d\n", mz);
//
//	printf("3:%04d\n", ax);
//	printf("4:%04d\n", ay);
//	printf("5:%04d\n", az);
//
//	printf("6:%04d\n", gx);
//	printf("7:%04d\n", gy);
//	printf("8:%04d\n", gz);

}

} // namespace
