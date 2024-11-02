#ifndef GENE_WITH_MIRROR_HPP_
#define GENE_WITH_MIRROR_HPP_

#include "Gene.hpp"
#include "RNG.hpp"

#include <iostream>
#include <memory>

class GeneWithMirror : public Gene {
 public:
  GeneWithMirror();
  GeneWithMirror(std::vector<double> values);

  std::vector<double> getGeneValues() const override;
  void setGeneValues(std::vector<double> values) override;
  const std::vector<std::pair<double, double>>& getConstraints() const override;

  void printGene() override;

  bool operator<(const Gene& other) const override;

 private:
  std::vector<double> values;
  const std::vector<std::pair<double, double>> constraints{{0, 20}, {0, 20}, {0, 3.14159265}};
};

#endif