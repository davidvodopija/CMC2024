#ifndef SELECTION_HPP_
#define SELECTION_HPP_

#include "Population.hpp"
#

class Selection {
 public:
  static Individual tournamentSelection(const Population& population, size_t k, bool best);
};

#endif