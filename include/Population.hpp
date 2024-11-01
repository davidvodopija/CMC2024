#ifndef POPULATION_HPP_
#define POPULATION_HPP_

#include "Individual.hpp"

#include <iostream>
#include <set>

class Population {
 public:
  void initialize(std::size_t size);

  std::set<Individual>& getIndividuals();

  void addIndividual(Individual individual);
  void removeIndividual(Individual individual);
  const Individual getBestIndividual();

 private:
  std::set<Individual> individuals;
};

#endif