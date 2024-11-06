#ifndef INDIVIDUAL_HPP_
#define INDIVIDUAL_HPP_

#include <iostream>
#include <vector>


class Individual {
 public:
  Individual();
  Individual(std::vector<float> genome);

  std::vector<float> getGenome() const;

  float getFitness() const;

  bool operator<(const Individual& other) const;

  void printIndividual() const;

  static Individual generateRandomIndividual(std::size_t size);

  static const std::vector<std::pair<float, float>> constraints;

 private:
  std::vector<float> genome;
  float fitness;
};

#endif