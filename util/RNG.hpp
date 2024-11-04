#ifndef RNG_HPP_
#define RNG_HPP_

#include <chrono>
#include <random>

class RNG {
 public:
  static int generate_random_int(int lb, int ub);
  static double generate_random_double(double lb, double ub);
  static int generate_random_binomial(int trials, double probability);
  static double generate_random_gaussian(double value, double stddev);
};

#endif