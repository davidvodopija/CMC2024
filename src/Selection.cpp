#include "Selection.hpp"

#include "RNG.hpp"

int Selection::tournamentSelection(const int popSize, size_t k, bool best) {
  std::set<int> indices;

  while (indices.size() < k) {
    indices.emplace(RNG::generate_random_int(0, popSize - 1));
  }

  // const auto& individuals = population.getIndividuals();

  int targetIndex = best ? *indices.rbegin() : *indices.begin();
  return targetIndex;

  /*   auto it = individuals.begin();
    std::advance(it, targetIndex);

    return *it; */
}
