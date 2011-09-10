#ifndef ESTIMATOR_H_
#define ESTIMATOR_H_

namespace naxsoft {
    class Estimator {
      public:
        static void estimate(double x_n_plus, double K, double *mu, double *sigma_sqr_n);
    };
}

#endif /* ESTIMATOR_H_ */
