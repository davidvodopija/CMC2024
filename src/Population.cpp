#include "Population.hpp"

std::set<Individual> Population::getIndividuals() const { return individuals; }

void Population::addIndividual(Individual individual) {
  individuals.insert(individual);
  ++size;
}

void Population::removeIndividual(Individual individual) {
  individuals.erase(individual);
  --size;
}

const Individual Population::getBestIndividual() { return *individuals.rbegin(); }

const std::size_t Population::getSize() const { return size; }

void Population::printPopulation() {
  auto it = individuals.rbegin();
  for (size_t i = 0; i < size; ++i, ++it) {
    std::cout << "Individual" << i << ":" << std::endl;
    it->printIndividual();
  }
}