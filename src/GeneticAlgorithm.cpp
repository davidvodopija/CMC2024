#include "GeneticAlgorithm.hpp"

Individual GeneticAlgorithm::runGenerationalGA(int popSize, int genNum) {
  std::cout << "Initializing individuals:" << std::endl;
  Population pop = Population::initializeIndividuals<GeneWithMirror>(popSize);
  for (int i = 0; i < genNum; ++i) {
    std::cout << "GEN: " << i << std::endl;
    pop.getBestIndividual().printIndividual();
    Population newPop;
    for (int j = 0; j < popSize / 2; ++j) {
      Individual parent1 = Selection::tournamentSelection(pop, 4, true);
      Individual parent2;
      // do {
      parent2 = Selection::tournamentSelection(pop, 4, true);
      //} while (parent1 != parent2);
      newPop.addIndividual(Crossover::blendAlpha(parent1, parent2, 0.1));
      newPop.addIndividual(Crossover::blendAlpha(parent2, parent1, 0.1));
    }
    pop = newPop;
    newPop.clear();
  }
  return pop.getBestIndividual();
}