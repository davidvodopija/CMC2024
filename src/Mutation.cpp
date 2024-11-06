#include "Mutation.hpp"

#include "Individual.hpp"

void Mutation::mutate(std::vector<float>& genome) {
  size_t n = RNG::generate_random_binomial(genome.size(), MUTATION_CHANCE);
  std::set<int> indices;
  const std::vector<std::pair<float, float>> constraints = Individual::constraints;

  while (indices.size() < n) {
    indices.insert(RNG::generate_random_int(0, genome.size() - 1));
  }

  for (int index : indices) {
    switch (RNG::generate_random_int(0, 2)) {
      case 0:
        genome[index] = Util::clamp(
            (float)RNG::generate_random_gaussian(genome[index],
                                                 SMALL_DEVIATION * (constraints[index % constraints.size()].second -
                                                                    constraints[index % constraints.size()].first)),
            constraints[index % constraints.size()].first,
            constraints[index % constraints.size()].second);
        break;
      case 1:
        genome[index] = Util::clamp(
            (float)RNG::generate_random_gaussian(genome[index],
                                                 BIG_DEVIATION * (constraints[index % constraints.size()].second -
                                                                  constraints[index % constraints.size()].first)),
            constraints[index % constraints.size()].first,
            constraints[index % constraints.size()].second);
        break;
      case 2:
        genome[index] = RNG::generate_random_double(constraints[index % constraints.size()].first,
                                                    constraints[index % constraints.size()].second);
        break;
    };
  }
}
