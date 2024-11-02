#include "Population.hpp"

class Selection {
 public:
  static Individual tournamentSelection(const Population& population, size_t k, bool best);
};