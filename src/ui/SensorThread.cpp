#include "SensorThread.h"

namespace naxsoft {

//SensorThread::SensorThread() {
//	// TODO Auto-generated constructor stub
//
//}
//
//SensorThread::~SensorThread() {
//	// TODO Auto-generated destructor stub
//}

void SensorThread::run() {
	qDebug() << "hello from worker thread " << thread()->currentThreadId();

	//	naxsoft::Compass* compass = new naxsoft::Compass;


	// 966.9 km										50° 3' 59.0004"   -5° 32' 3.0012"    58° 38' 38.0004"    -3° 4' 11.9994"
	// printf("Distance %fkm\n", naxsoft::LatLon::calcDistance(50.06638888888889, -5.534166666666667, 58.64388888888889, -3.0700000000000003));
	// 9.1175°									50° 3' 51.0006"     -5° 42' 52.9992"      58° 38' 38.0004"	-3° 4' 11.9994"
	// printf("Bearing %f°\n", naxsoft::LatLon::getBearing(50.064166666666665, -5.714722222222222, 58.64388888888889, -3.0700000000000003));


	//	double decimalDegrees  = 50.064166666666665;
	//	naxsoft::dmsData dms;
	//	naxsoft::LatLon::decimalDegreesToDMS(decimalDegrees, &dms);
	//	printf("Decimal %f Equals Sexagesimal %d° %ld' %f\"\n", decimalDegrees, dms.degree, dms.min, dms.sec);

	naxsoft::SerialTransport transport("/dev/cu.usbserial-A70041iS", B9600);
	transport.open();

	if (!transport.isOpen()) {
		exit(EXIT_FAILURE);
	}

	naxsoft::Protocol protocol(&transport);
	naxsoft::SensorReader* sensorReader = new naxsoft::SensorReader(&protocol);
	//	naxsoft::DataLogger* dataLogger = new naxsoft::DataLogger();

	int16_t mx, my, mz = 0;
	int16_t ax, ay, az = 0;
	int16_t gx, gy, gz = 0;

	uint32_t rz = 0;

	//	accelerometer.setScale(18.0 / 256.0, 18.0 / 256.0, 18.0 / 256.0);

	//	accelerometer.setOffset(14, 21, -2);
	//	gyro.setOffset(-2, -14, -6);

	int i = 0;
	vector p = { 0, -1, 0};

	while (true) {
		do {
			rz = sensorReader->readAccelerometer(ax, ay, az);
			accelerometer.setAxis(ax, ay, az);
		} while (rz == 0);
		do {
			rz = sensorReader->readGyro(gx, gy, gz);
			gyro.setAxis(gx, gy, gz);
		} while (rz == 0);
		do {
			rz = sensorReader->readMagnetometer(mx, my, mz);
			compass.setAxis(mx, my, mz);
		} while (rz == 0);

		double r = accelerometer.getForceVector();
		double accXangle = naxsoft::LatLon::radToDegrees(accelerometer.getXangle(r)); // when flat x & y are 90 deg to z
		double accYangle = naxsoft::LatLon::radToDegrees(accelerometer.getYangle(r));

		//		compass.compensatedTilt(3.122, 3);
		double heading1 = compass.getHeading(gyro.getRoll(), gyro.getPitch());
		double azimuth = compass.getAzimuth();

		a.x = accelerometer.getSway();
		a.y = accelerometer.getHeave();
		a.z = accelerometer.getSurge();
		m.x = compass.getX();
		m.y = compass.getY();
		m.z = compass.getZ();

		double heading2 = compass.getHeading(&a, &m, &p);

		//		dataLogger->log(0, 0, 0,    0, 0, 0,    0, 0, 0, i);
		//		dataLogger->log(heading, azimuth, 0,    accelerometer.getSway(), accelerometer.getHeave(), accelerometer.getSurge(), gyro.getPitch(), gyro.getYaw(), gyro.getRoll(), i);
		//		dataLogger->log(0, 0, 0, accXangle, accYangle, 0, accelerometer.getSurge(), accelerometer.getSway(), accelerometer.getHeave(), i);
		// 		dataLogger->log(mx, my, mz, accelerometer.getSway(), accelerometer.getHeave(), accelerometer.getSurge(), gyro.getPitch(), gyro.getYaw(), gyro.getRoll(), i);
		// 		dataLogger->log(heading1, heading2, azimuth, accelerometer.getSway(), accelerometer.getHeave(), accelerometer.getSurge(), gyro.getPitch(), gyro.getYaw(), gyro.getRoll(), i);
		// 		dataLogger->log(accXangle, accYangle, 0, accelerometer.getSurge(), accelerometer.getSway(), accelerometer.getHeave(), gyro.getPitch(), gyro.getYaw(), gyro.getRoll(), i);

		//		printf("%04.2f\t%04.2f\t", accXangle, accYangle);
		//		printf("%04.2f\t%04.2f\t%04.2f\t", heading1, heading2, azimuth);
		//		printf("%04.2f\t%04.2f\t%04.2f\t", compass.getX(), compass.getY(), compass.getZ());
		printf("%04.2f\t%04.2f\t%04.2f\t", accelerometer.getSway(), accelerometer.getHeave(), accelerometer.getSurge());
		printf("%04.2f\t%04.2f\t%04.2f\t%d\n", gyro.getPitch(), gyro.getRoll(), gyro.getYaw(), i);


		emit updateAzimuth(azimuth) ;

		//		printf("maxAcceleration = %f\n", accelerometer.maxAcceleration());

		i++;
	}

}

}
