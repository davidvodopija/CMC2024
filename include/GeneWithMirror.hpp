#ifndef GENE_WITH_MIRROR_HPP_
#define GENE_WITH_MIRROR_HPP_

#include "Gene.hpp"

#include <math.h>

#include <vector>

class GeneWithMirror : public Gene {
 public:
  GeneWithMirror();
  GeneWithMirror(std::vector<double> values);

  std::vector<double> getGeneValues() const override = 0;
  void setGeneValues(std::vector<double> values) = 0;
  const std::vector<std::pair<double, double>> getConstraints() const = 0;

  bool operator<(const Gene& other) const;

  static void crossover(const Gene& gene1, const Gene& gene2, Gene& result);

 private:
  std::vector<double> values;
  const std::vector<std::pair<double, double>> constraints;
};

#endif GENE_WITH_MIRROR_HPP_