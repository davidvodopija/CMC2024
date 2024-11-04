#include "Crossover.hpp"

Individual Crossover::blendAlpha(const Individual& ind1, const Individual& ind2, double alpha) {
  const auto flatInd1 = ind1.flattenIndividual();
  const auto flatInd2 = ind2.flattenIndividual();
  bool success = false;
  Individual newIndividual;

  while (!success) {
    std::vector<double> newGenome;
    try {
      size_t n = RNG::generate_random_binomial(flatInd1.first.size(), CROSSOVER_CHANCE);
      std::set<int> indices;
      while (indices.size() < n) {
        indices.insert(RNG::generate_random_int(0, flatInd1.first.size() - 1));
      }
      for (size_t i = 0; i < flatInd1.first.size(); ++i) {
        if (indices.find(i) != indices.end()) {
          newGenome.push_back(
              Util::clamp(RNG::generate_random_double(std::min(flatInd1.first[i], flatInd2.first[i]) -
                                                          std::abs(flatInd1.first[i] - flatInd2.first[i]) * alpha,
                                                      std::max(flatInd1.first[i], flatInd2.first[i]) +
                                                          std::abs(flatInd1.first[i] - flatInd2.first[i]) * alpha),
                          flatInd1.second[i].first,
                          flatInd1.second[i].second));
        }
        else {
          newGenome.push_back(flatInd1.first[i]);
        }
      }
      Mutation::mutate(newGenome, flatInd1.second);
      std::vector<std::shared_ptr<Gene>> newGenes = ind1.getGene(0)->getFilledClones(newGenome);
      Individual tmpInd{newGenes};
      success = true;
      newIndividual = tmpInd;
    }
    catch (const std::exception& e) {
      std::cout << "Individual construciton after mutation failed, trying again..." << std::endl;
    }
  }
  return newIndividual;
}