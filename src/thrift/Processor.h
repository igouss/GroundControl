#ifndef PROCESSOR_H_
#define PROCESSOR_H_

namespace naxsoft {
    class Protocol; // Forward declaration

    class Processor {
      public:
        bool process(Protocol const* in, Protocol  const* out);
      private:
        bool processDcMotor(Protocol  const* in);
        bool tlc(Protocol  const* in);
    	bool accelerometer(Protocol const* in);
    	bool compass(Protocol const* in);
    	bool gyroscope(Protocol const* in);
    };

    extern Processor processor;
}

#endif /* PROCESSOR_H_ */
