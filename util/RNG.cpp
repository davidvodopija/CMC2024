#include "RNG.hpp"

int RNG::generate_random_int(int lb, int ub) {
  static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> dist(lb, ub);
  return dist(gen);
}

double RNG::generate_random_double(double lb, double ub) {
  static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());  // Mersenne Twister engine
  std::uniform_real_distribution<double> dist(lb, ub);
  return dist(gen);
}

int RNG::generate_random_binomial(int trials, double probability) {
  static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());  // Mersenne Twister engine
  std::binomial_distribution<int> dist(trials, probability);
  return dist(gen);
}