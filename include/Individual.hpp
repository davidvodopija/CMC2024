#ifndef INDIVIDUAL_HPP_
#define INDIVIDUAL_HPP_

#include "Gene.hpp"
#include "GeneWithMirror.hpp"

class Individual {
 public:
  Individual();
  Individual(std::vector<std::shared_ptr<Gene>> genome);

  std::vector<std::shared_ptr<Gene>> getGenome() const;
  std::shared_ptr<Gene> getGene(std::size_t index) const;

  double getFitness() const;

  bool operator<(const Individual& other) const;

  std::vector<double> flattenIndividual();

  void printIndividual() const;

  template <typename GeneType>
  static Individual generateRandomIndividual() {
    bool success = false;
    Individual individual;
    while (!success) {
      try {
        std::vector<std::shared_ptr<Gene>> genome;

        for (int i = 0; i < 9; ++i) {
          genome.push_back(std::make_shared<GeneType>());
        }
        Individual tmpIndividual{genome};
        success = true;
        individual = tmpIndividual;
      }
      catch (const std::exception& e) {
        std::cout << "Individual construciton failed, trying again..." << std::endl;
      }
    }
    return individual;
  }

 private:
  std::vector<std::shared_ptr<Gene>> genome;
  double fitness;
};

#endif