#ifndef GENE_HPP_
#define GENE_HPP_

#include <memory>
#include <vector>

class Gene {
 public:
  virtual ~Gene() = default;

  virtual const std::vector<double>& getGeneValues() const = 0;
  virtual void setGeneValues(std::vector<double> values) = 0;
  virtual const std::vector<std::pair<double, double>>& getConstraints() const = 0;
  virtual std::vector<std::shared_ptr<Gene>> getFilledClones(const std::vector<double>& genes) = 0;

  virtual bool operator<(const Gene& other) const = 0;

  virtual void printGene() = 0;
};

#endif