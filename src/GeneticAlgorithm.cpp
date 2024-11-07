#include "GeneticAlgorithm.hpp"

Individual GeneticAlgorithm::runGenerationalGA(int popSize, int genNum) {
  std::cout << "Initializing individuals:" << std::endl;
  Population pop = Population::initializeIndividuals(popSize);
  for (int i = 0; i < genNum; ++i) {
    std::cout << "GEN: " << i << std::endl;
    pop.getBestIndividual().printIndividual();
    Population newPop;
    for (int j = 0; j < popSize / 2; ++j) {
      int index1 = Selection::tournamentSelection(pop.getSize(), 4, true);
      int index2;
      do {
        index2 = Selection::tournamentSelection(pop.getSize(), 4, true);
      } while (index1 == index2);

      Individual parent1, parent2;
      {
        const auto& individuals = pop.getIndividuals();
        auto it = individuals.begin();
        std::advance(it, index1);
        parent1 = *it;
      }
      {
        const auto& individuals = pop.getIndividuals();
        auto it = individuals.begin();
        std::advance(it, index2);
        parent2 = *it;
      }
      newPop.addIndividual(Crossover::blendAlpha(parent1, parent2, 0.1));
      newPop.addIndividual(Crossover::blendAlpha(parent2, parent1, 0.1));
    }
    pop = newPop;
    newPop.clear();
  }
  return pop.getBestIndividual();
}