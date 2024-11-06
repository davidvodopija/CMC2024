#include "Crossover.hpp"

Individual Crossover::blendAlpha(const Individual& ind1, const Individual& ind2, float alpha) {
  bool success = false;
  Individual newIndividual;

  const std::vector<float>& genome1 = ind1.getGenome();
  const std::vector<float>& genome2 = ind2.getGenome();

  while (!success) {
    std::vector<float> newGenome;
    try {
      size_t n = RNG::generate_random_binomial(genome1.size(), CROSSOVER_CHANCE);
      std::set<int> indices;
      while (indices.size() < n) {
        indices.insert(RNG::generate_random_int(0, genome1.size() - 1));
      }
      for (size_t i = 0; i < genome1.size(); ++i) {
        if (indices.find(i) != indices.end()) {
          newGenome.push_back(
              Util::clamp((float)RNG::generate_random_double(
                              std::min(genome1[i], genome2[i]) - std::abs(genome1[i] - genome2[i]) * alpha,
                              std::max(genome1[i], genome2[i]) + std::abs(genome1[i] - genome2[i]) * alpha),
                          Individual::constraints[i % Individual::constraints.size()].first,
                          Individual::constraints[i % Individual::constraints.size()].second));
        }
        else {
          newGenome.push_back(genome1[i]);
        }
      }
      Mutation::mutate(newGenome);
      Individual tmpInd{newGenome};
      success = true;
      newIndividual = tmpInd;
    }
    catch (const std::exception& e) {
      // std::cout << "Individual construciton after mutation failed, trying again..." << std::endl;
    }
  }
  return newIndividual;
}