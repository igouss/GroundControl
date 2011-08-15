#ifndef CALIBRATOR_H_
#define CALIBRATOR_H_

namespace naxsoft {

class Calibrator {
public:
	Calibrator();
	virtual ~Calibrator();
	void calibrateAccelerometer();
};

}

#endif /* CALIBRATOR_H_ */
