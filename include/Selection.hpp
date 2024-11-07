#ifndef SELECTION_HPP_
#define SELECTION_HPP_

#include "Population.hpp"

class Selection {
 public:
  static int tournamentSelection(const int popSize, size_t k, bool best);
};

#endif