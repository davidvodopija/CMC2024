#ifndef CROSSOVER_HPP_
#define CROSSOVER_HPP_

#define CROSSOVER_CHANCE 0.05

#include "Individual.hpp"
#include "Mutation.hpp"

#include <algorithm>
#include <set>

class Crossover {
 public:
  static Individual blendAlpha(const Individual& ind1, const Individual& ind2, float alpha);
};

#endif