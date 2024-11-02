#include "RNG.hpp"

#include <random>

double RNG::generate_random_double(double lb, double ub) {
  static std::random_device rd;   // Seed source
  static std::mt19937 gen(rd());  // Mersenne Twister engine
  std::uniform_real_distribution<double> dist(lb, ub);
  return dist(gen);
}

int RNG::generate_random_binomial(int trials, double probability) {
  static std::random_device rd;   // Seed source
  static std::mt19937 gen(rd());  // Mersenne Twister engine
  std::binomial_distribution<int> dist(trials, probability);
  return dist(gen);
}