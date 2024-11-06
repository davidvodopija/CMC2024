#include "RNG.hpp"
#include "Util.hpp"
#define MUTATION_CHANCE 0.05
#define SMALL_DEVIATION 0.05
#define BIG_DEVIATION 0.1
#include <set>

class Mutation {
 public:
  static void mutate(std::vector<float>& genome);
};