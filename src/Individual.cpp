#include "Individual.hpp"

#include "GeneWithMirror.hpp"
#include "RNG.hpp"

#include <ctime>
#include <iostream>

Individual::Individual(std::vector<std::shared_ptr<Gene>> genome) {
  this->genome = genome;
  fitness = RNG::generate_random_double(0, 100);  // temporary, dok ne spojim sa cindrinim kodom: POZIV EVALUACIJE
}

std::vector<std::shared_ptr<Gene>> Individual::getGenome() const { return genome; }

std::shared_ptr<Gene> Individual::getGene(std::size_t index) const { return genome[index]; }

double Individual::getFitness() const { return fitness; }

bool Individual::operator<(const Individual& other) const {
  if (fitness != other.getFitness()) return fitness < other.getFitness();

  return std::lexicographical_compare(
      genome.begin(),
      genome.end(),
      other.getGenome().begin(),
      other.getGenome().end(),
      [](const std::shared_ptr<Gene>& a, const std::shared_ptr<Gene>& b) { return *a < *b; });
}

std::vector<double> Individual::flattenIndividual() {
  std::vector<double> result;
  for (auto gene : genome) {
    result.insert(result.end(), gene->getGeneValues().begin(), gene->getGeneValues().end());
  }
  return result;
}

void Individual::printIndividual() {
  for (size_t i = 0; i < genome.size(); ++i) {
    std::cout << "Gene" << i << ": ";
    genome[i]->printGene();
  }
  std::cout << "FITNESS: " << fitness << std::endl;
}

template <typename GeneType>
Individual Individual::generateRandomIndividual() {
  std::vector<std::shared_ptr<Gene>> genome;

  for (int i = 0; i < 9; ++i) {
    genome.push_back(std::make_shared<GeneType>());
  }
  return Individual{genome};
}