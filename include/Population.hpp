#ifndef POPULATION_HPP_
#define POPULATION_HPP_

#include "Individual.hpp"

#include <set>

class Population {
 public:
  std::set<Individual> getIndividuals() const;
  void addIndividual(Individual individual);
  void removeIndividual(Individual individual);
  const Individual getBestIndividual();
  const std::size_t getSize() const;
  void clear();

  void printPopulation();

  // Default constructor should not be used, instead population should be initialized through this function
  static Population initializeIndividuals(size_t size);

 private:
  std::set<Individual> individuals{};
  std::size_t size{0};
};

#endif