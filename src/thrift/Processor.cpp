#include <stdint.h>   /* Standard types */

#include "Processor.h"
#include "Protocol.h"

#define DC_MOTOR_SPEED 1
#define TLC 4

#define ACCELEROMETER 5
#define COMPASS 6
#define GYROSCOPE 7

namespace naxsoft {

Processor processor; // preinstatiate

bool Processor::process(Protocol const* const in, Protocol const* const out) {
	(void) out;

	//  Serial.println("Processor::process");
	int8_t rpc = 0;
	//	  char name = 0;
	TMessageType messageType;
	//	  int32_t seqid = 0;
	in->readMessageBegin(messageType);

	//  Serial.print("name = ");
	//  Serial.println(name);
	//  Serial.print("messageType = ");
	//  Serial.println(messageType);
	//  Serial.print("seqid = ");
	//  Serial.println(seqid);

	in->readI8(rpc);
//	Serial.print("RPC = ");
//	Serial.println(rpc);

	bool result = true;
	switch (rpc) {
	case DC_MOTOR_SPEED:
		result = this->processDcMotor(in);
		break;
	case TLC:
		result = this->tlc(in);
		break;
	case ACCELEROMETER:
		result = this->accelerometer(in);
		break;
	case COMPASS:
		result = this->compass(in);
		break;
	case GYROSCOPE:
		result = this->gyroscope(in);
		break;
	default:
		result = false;
	};
	in->readMessageEnd();
	return result;
}

bool Processor::processDcMotor(Protocol const* const in) {
	(void) in;

//	int8_t motor1;
//	int8_t motor2;
//	int8_t motor3;
//	int8_t motor4;
//	int16_t speed1;
//	int16_t speed2;
//	int16_t speed3;
//	int16_t speed4;
//	int8_t direction1;
//	int8_t direction2;
//	int8_t direction3;
//	int8_t direction4;
//
//	in->readI8(motor1);
//	in->readI8(motor2);
//	in->readI8(motor3);
//	in->readI8(motor4);
//	in->readI16(speed1);
//	in->readI16(speed2);
//	in->readI16(speed3);
//	in->readI16(speed4);
//	in->readI8(direction1);
//	in->readI8(direction2);
//	in->readI8(direction3);
//	in->readI8(direction4);
//	dcMotor.start(motor1, speed1, direction1);
//	dcMotor.start(motor2, speed2, direction2);
//	dcMotor.start(motor3, speed3, direction3);
//	dcMotor.start(motor4, speed4, direction4);
	return true;
}

bool Processor::tlc(Protocol const* in) {
	(void) in;

//	// Serial.println("Processor::tlc");
//	int8_t channel;
//	int8_t value;
//
//	in->readI8(channel);
//	// Serial.print("channel = ");
//	// Serial.println(channel);
//
//	in->readI8(value);
//	// Serial.print("value = ");
//	// Serial.println(value);
//
//	Tlc.set(channel, value);
	return true;
}

bool Processor::accelerometer(Protocol const* in) {
	(void) in;

//	accelerometer_data adata;
//	naxsoft::accelerometer.read(&adata);
//
//	Serial.print("Accelerometer: ");
//	Serial.print("X: ");
//	Serial.print(-adata.x);
//	Serial.print(" Y: ");
//	Serial.print(-adata.y);
//	Serial.print(" Z: ");
//	Serial.println(-adata.z);

	return true;
}

bool Processor::compass(Protocol const* in) {
	(void) in;

//	compass_data cdata;
//	naxsoft::compass.read(&cdata);
//
//	Serial.print("      Compass: ");
//	Serial.print("X: ");
//	Serial.print(-cdata.x);
//	Serial.print(" Y: ");
//	Serial.print(-cdata.y);
//	Serial.print(" Z: ");
//	Serial.println(-cdata.z);

	return true;
}

bool Processor::gyroscope(Protocol const* in) {
	(void) in;
//	gyroscope_data gdata;
//	naxsoft::gyroscope.getGyroValues(&gdata); // This will update x, y, and z with new values
//
//	Serial.print("    Gyroscope:  ");
//	Serial.print(" Yaw: ");
//	Serial.print(gdata.x);
//	Serial.print(" Pitch: ");
//	Serial.print(gdata.y);
//	Serial.print(" Roll: ");
//	Serial.println(gdata.z);

	return true;
}
} // namespace
