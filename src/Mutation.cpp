#include "Mutation.hpp"

void Mutation::mutate(std::vector<double>& genome, const std::vector<std::pair<double, double>>& constraints) {
  size_t n = RNG::generate_random_binomial(genome.size(), MUTATION_CHANCE);
  std::set<int> indices;

  while (indices.size() < n) {
    indices.insert(RNG::generate_random_int(0, genome.size() - 1));
  }

  for (int index : indices) {
    switch (RNG::generate_random_int(0, 2)) {
      case 0:
        genome[index] =
            Util::clamp(RNG::generate_random_gaussian(
                            genome[index], SMALL_DEVIATION * (constraints[index].second - constraints[index].first)),
                        constraints[index].first,
                        constraints[index].second);
        break;
      case 1:
        genome[index] =
            Util::clamp(RNG::generate_random_gaussian(
                            genome[index], BIG_DEVIATION * (constraints[index].second - constraints[index].first)),
                        constraints[index].first,
                        constraints[index].second);
        break;
      case 2:
        genome[index] = RNG::generate_random_double(constraints[index].first, constraints[index].second);
        break;
    };
  }
}
