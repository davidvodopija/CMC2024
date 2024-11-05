#include "Selection.hpp"

#include "RNG.hpp"

Individual Selection::tournamentSelection(const Population& population, size_t k, bool best) {
  std::set<int> indices;

  while (indices.size() < k) {
    indices.emplace(RNG::generate_random_int(0, population.getSize() - 1));
  }

  const auto& individuals = population.getIndividuals();

  int targetIndex = best ? *indices.rbegin() : *indices.begin();

  // std::cout << targetIndex << " ";

  auto it = individuals.begin();
  std::advance(it, targetIndex);

  return *it;
}
