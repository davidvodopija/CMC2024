#include "Individual.hpp"

#include "GeneticAlgorithm.hpp"
#include "main.hpp"

#include <stdexcept>

Individual::Individual() {
  fitness = 0;
  genome = {};
}

Individual::Individual(std::vector<std::shared_ptr<Gene>> genome) {
  this->genome = genome;
  fitness = start_eval(flattenIndividual().first);
  if (fitness == 0) throw std::invalid_argument("invalid game position");
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

std::pair<std::vector<double>, std::vector<std::pair<double, double>>> Individual::flattenIndividual() const {
  std::pair<std::vector<double>, std::vector<std::pair<double, double>>> result;
  for (auto gene : genome) {
    result.first.insert(result.first.end(), gene->getGeneValues().begin(), gene->getGeneValues().end());
    result.second.insert(result.second.end(), gene->getConstraints().begin(), gene->getConstraints().end());
  }
  return result;
}

void Individual::printIndividual() const {
  for (size_t i = 0; i < genome.size(); ++i) {
    std::cout << "Gene" << i << ": ";
    genome[i]->printGene();
  }
  std::cout << "FITNESS: " << fitness << std::endl;
}

int main(void) {
  GeneticAlgorithm::runGenerationalGA(100, 1000).printIndividual();
  return 0;
}