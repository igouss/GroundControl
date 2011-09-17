#ifndef SENSORTHREAD_H_
#define SENSORTHREAD_H_

#include <QtCore>

#include "thrift/Protocol.h"
#include "thrift/SerialTransport.h"

#include "sensors/Compass.h"
#include "sensors/Accelerometer.h"
#include "sensors/Gyroscope.h"
#include "sensors/Vector.h"

#include "SensorReader.h"
#include "DataLogger.h"
#include "LatLon.h"


namespace naxsoft {

class SensorThread  : public QThread
{
    Q_OBJECT
//public:
//	SensorThread();
//	virtual ~SensorThread();

signals:
	void updateAzimuth(qreal azimuth);

private:
    void run();


    Compass compass;
    Accelerometer accelerometer;
    Gyroscope gyro;

    vector m;
    vector a;
//    vector p;
}; // class

} // namespace

#endif /* SENSORTHREAD_H_ */
