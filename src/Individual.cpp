#include "Individual.hpp"

#include <stdexcept>

Individual::Individual() {
  fitness = 0;
  genome = {};
}

Individual::Individual(std::vector<std::shared_ptr<Gene>> genome) {
  this->genome = genome;
  fitness = RNG::generate_random_double(0, 100);  // temporary, dok ne spojim sa cindrinim kodom: POZIV EVALUACIJE
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

std::vector<double> Individual::flattenIndividual() {
  std::vector<double> result;
  for (auto gene : genome) {
    result.insert(result.end(), gene->getGeneValues().begin(), gene->getGeneValues().end());
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