#include "RNG.hpp"

#include <random>

double RNG::generate_random_double(double lb, double ub) { return sqrt((double)rand() / RAND_MAX) * ub + lb; }