#ifndef GENE_HPP_
#define GENE_HPP_

#include <vector>

class Gene {
 public:
  virtual std::vector<double> getGeneValues() const = 0;
  virtual void setGeneValues(std::vector<double> values) = 0;
  virtual const std::vector<std::pair<double, double>> getConstraints() const = 0;

  virtual bool operator<(const Gene& other) const = 0;

  static void crossover(const Gene& gene1, const Gene& gene2, Gene& result);
};

#endif