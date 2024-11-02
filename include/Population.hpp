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

  void printPopulation();

  // Default constructor should not be used, instead population should be initialized through this function
  template <typename GeneType>
  static Population initializeIndividuals(size_t size) {
    Population population;
    while (size > 0) {
      population.addIndividual(Individual::generateRandomIndividual<GeneType>());
      --size;
    }
    return population;
  }

 private:
  std::set<Individual> individuals{};
  std::size_t size{0};
};

#endif