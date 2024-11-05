#include "Crossover.hpp"
#include "Population.hpp"
#include "Selection.hpp"

class GeneticAlgorithm {
 public:
  static Individual runGenerationalGA(int popSize, int genNum);
};