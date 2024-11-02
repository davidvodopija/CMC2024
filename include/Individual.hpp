#ifndef INDIVIDUAL_HPP_
#define INDIVIDUAL_HPP_

#include "Gene.hpp"

#include <memory>
#include <vector>

class Individual {
 public:
  Individual(std::vector<std::shared_ptr<Gene>> genome);

  std::vector<std::shared_ptr<Gene>> getGenome() const;
  std::shared_ptr<Gene> getGene(std::size_t index) const;

  double getFitness() const;

  bool operator<(const Individual& other) const;

  std::vector<double> flattenIndividual();

  void printIndividual();

  template <typename GeneType>
  static Individual generateRandomIndividual();

 private:
  std::vector<std::shared_ptr<Gene>> genome;
  double fitness;
};

#endif