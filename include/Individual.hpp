#ifndef INDIVIDUAL_HPP_
#define INDIVIDUAL_HPP_

#include "Gene.hpp"

#include <vector>

class Individual {
 public:
  Individual(std::vector<Gene> genome);

  std::vector<Gene> getGenome() const;
  Gene getGene(std::size_t index) const;

  double getFitness() const;
  double setFintess();

  bool operator<(const Individual& other) const;

  template <typename GeneType>
  static Individual generateRandomIndividual();

 private:
  std::vector<Gene> genome;
  double fitness;
};

#endif