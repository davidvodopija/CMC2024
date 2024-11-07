#include "Population.hpp"

std::multiset<Individual> Population::getIndividuals() const { return individuals; }

void Population::addIndividual(Individual individual) {
  individuals.insert(individual);
  ++size;
}

void Population::removeIndividual(Individual individual) {
  auto it = individuals.find(individual);  // Finds one occurrence of the individual
  if (it != individuals.end()) {
    individuals.erase(it);  // Only erases one instance if duplicates exist
  }
  --size;
}

const Individual Population::getBestIndividual() { return *individuals.rbegin(); }

const std::size_t Population::getSize() const { return size; }

void Population::clear() {
  individuals.clear();
  size = 0;
}

void Population::printPopulation() {
  auto it = individuals.rbegin();
  for (size_t i = 0; i < size; ++i, ++it) {
    std::cout << "Individual" << i << ":" << std::endl;
    it->printIndividual();
  }
}

Population Population::initializeIndividuals(size_t size) {
  Population population;
  for (size_t i = 0; i < size; ++i) {
    population.addIndividual(Individual::generateRandomIndividual(18));  // FLAG
    std::cout << i + 1 << "/" << size << std::endl;
  }
  return population;
}