#include "KalmanFilter.h"

namespace naxsoft {

KalmanFilter::KalmanFilter() {
	// TODO Auto-generated constructor stub

}

KalmanFilter::~KalmanFilter() {
	// TODO Auto-generated destructor stub
}

#include <math.h>

float dt = .06; //( 1024.0 * 256.0 ) / 16000000.0; (Kalman)
int mydt = 20; //in ms.
static float P[2][2] = { { 1, 0 }, { 0, 1 }, }; //(Kalman)


/*
 * Our two states, the angle and the gyro bias.  As a byproduct of computing
 * the angle, we also have an unbiased angular rate available.   These are
 * read-only to the user of the module.
 */
float angle; //(Kalman)
float q_bias; //(Kalman)
float rate; //(Kalman)
float q_m; //(Kalman)

int ax_m = 0; //NunChuck X acceleration
int az_m = 0; //NunChuck Z acceleration
int cnt = 0; //Counter
unsigned long lastread = 0;

/*
 * R represents the measurement covariance noise.  In this case,
 * it is a 1x1 matrix that says that we expect 0.3 rad jitter
 * from the accelerometer.
 */
float R_angle = .3; //.3 deafault, but is adjusted externally (Kalman)


/*
 * Q is a 2x2 matrix that represents the process covariance noise.
 * In this case, it indicates how much we trust the acceleromter
 * relative to the gyros.
 */
static const float Q_angle = 0.001; //(Kalman)
static const float Q_gyro = 0.003; //(Kalman)

void loop() {
	if ((millis() - lastread) >= mydt) { // sample every dt ms -> 1000/dt hz.
		lastread = millis();
		q_m = ((average * (joy_x_axis * 0.00392156862)) / (180 / PI)); //GYRO convertion to Radian and external correction with nunchuk joystick

		/* Unbias our gyro */
		const float q = q_m - q_bias; //(Kalman)

		const float Pdot[2 * 2] = { Q_angle - P[0][1] - P[1][0], /* 0,0 *///(Kalman)
				-P[1][1], /* 0,1 */
				-P[1][1], /* 1,0 */
				Q_gyro /* 1,1 */
		};

		/* Store our unbias gyro estimate */
		rate = q; //(Kalman)

		/*
		 * Update our angle estimate
		 * angle += angle_dot * dt
		 *       += (gyro - gyro_bias) * dt
		 *       += q * dt
		 */
		angle += q * dt; //(Kalman)

		/* Update the covariance matrix */
		P[0][0] += Pdot[0] * dt; //(Kalman)
		P[0][1] += Pdot[1] * dt; //(Kalman)
		P[1][0] += Pdot[2] * dt; //(Kalman)
		P[1][1] += Pdot[3] * dt; //(Kalman)


		Wire.requestFrom(0x52, 6); // request data from nunchuck

		while (Wire.available()) //(NunChuck)
		{
			outbuf[cnt] = nunchuk_decode_byte(Wire.receive()); // receive byte as an integer //(NunChuck)
			cnt++;//(NunChuck)
		}

		send_zero(); // send the request for next bytes
		// If we recieved the 6 bytes, then print them //(NunChuck)
		if (cnt >= 5) //(NunChuck)
		{
			print(); //(NunChuck)
		}
		cnt = 0; //(NunChuck)

		R_angle = (joy_y_axis + 1) * 0.0098039; //external adjust jitter of accelerometer with nunchuck joystick

		const float angle_m = atan2(ax_m, az_m); //(Kalman)
		const float angle_err = angle_m - angle; //(Kalman)
		const float C_0 = 1; //(Kalman)
		const float PCt_0 = C_0 * P[0][0]; //(Kalman)
		const float PCt_1 = C_0 * P[1][0]; //(Kalman)
		const float E = R_angle + C_0 * PCt_0; //(Kalman)
		const float K_0 = PCt_0 / E; //(Kalman)
		const float K_1 = PCt_1 / E; //(Kalman)
		const float t_0 = PCt_0; /* C_0 * P[0][0] + C_1 * P[1][0] (Kalman) */

		const float t_1 = C_0 * P[0][1]; /* + C_1 * P[1][1]  = 0 (Kalman) */

		P[0][0] -= K_0 * t_0; //(Kalman)
		P[0][1] -= K_0 * t_1; //(Kalman)
		P[1][0] -= K_1 * t_0; //(Kalman)
		P[1][1] -= K_1 * t_1; //(Kalman)
		angle += K_0 * angle_err; //(Kalman)
		q_bias += K_1 * angle_err; //(Kalman)


		Serial.print(joy_y_axis); //Prints the adjust for accelerometer jitter
		Serial.print(" ");
		Serial.print(int(angle_m * 57.295779513082)); //Prints the accelometer
		Serial.print(" ");
		Serial.print(int(angle * 57.2957795130823)); //Prints degrees Acceleromter+Gyros+KalmanFilters
		Serial.print(" ");
		Serial.println(joy_x_axis); //Prints the Gyro adjusment


	}

}

} // namespace
