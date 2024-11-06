#include "Individual.hpp"

#include "GeneticAlgorithm.hpp"
#include "main.hpp"

#include <stdexcept>

Individual::Individual() {
  fitness = 0;
  genome = {};
}

Individual::Individual(std::vector<float> genome) {
  this->genome = genome;
  fitness = start_eval(genome);
  if (fitness == 0) throw std::invalid_argument("invalid game position");
}

std::vector<float> Individual::getGenome() const { return genome; }

float Individual::getFitness() const { return fitness; }

bool Individual::operator<(const Individual& other) const {
  if (fitness != other.getFitness()) return fitness < other.getFitness();
  return genome < other.getGenome();
}

void Individual::printIndividual() const {
  for (size_t i = 0; i < genome.size(); ++i) {
    std::cout << genome[i] << " ";
  }
  std::cout << std::endl << "FITNESS: " << fitness << std::endl;
}

Individual Individual::generateRandomIndividual(size_t size) {
  bool success = false;
  Individual individual;
  while (!success) {
    try {
      std::vector<float> genome;

      for (size_t i = 0; i < size; ++i) {
        genome.push_back(RNG::generate_random_double(Individual::constraints[i % constraints.size()].first,
                                                     Individual::constraints[i % constraints.size()].second));
      }
      Individual tmpIndividual{genome};
      success = true;
      individual = tmpIndividual;
    }
    catch (const std::exception& e) {
      // std::cout << "Individual construciton failed, trying again..." << std::endl;
    }
  }
  return individual;
}

const std::vector<std::pair<float, float>> Individual::constraints{{0, 20}, {0, 20}, {0, pi}};

int main(void) {
  GeneticAlgorithm::runGenerationalGA(10, 100).printIndividual();
  return 0;
}