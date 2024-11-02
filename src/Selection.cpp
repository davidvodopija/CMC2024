#include "Selection.hpp"

Individual Selection::tournamentSelection(const Population& population, size_t k, bool best) {
  std::set<int> indices;

  while (indices.size() < k) {
    indices.emplace(rand() % population.getSize());
  }

  const auto& individuals = population.getIndividuals();

  int targetIndex = best ? *indices.rbegin() : *indices.begin();

  std::cout << targetIndex << " ";

  auto it = individuals.begin();
  std::advance(it, targetIndex);

  return *it;
}
