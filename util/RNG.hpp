#ifndef RNG_HPP_
#define RNG_HPP_

class RNG {
 public:
  static double generate_random_double(double lb, double ub);
  static int generate_random_binomial(int trials, double probability);
};

#endif