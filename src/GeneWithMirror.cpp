#include "GeneWithMirror.hpp"

GeneWithMirror::GeneWithMirror() {
  values.push_back(RNG::generate_random_double(constraints[0].first, constraints[0].second));
  values.push_back(RNG::generate_random_double(constraints[1].first, constraints[1].second));
  values.push_back(RNG::generate_random_double(constraints[2].first, constraints[2].second));
}

const std::vector<double>& GeneWithMirror::getGeneValues() const { return values; }

void GeneWithMirror::setGeneValues(std::vector<double> values) { this->values = values; }

const std::vector<std::pair<double, double>>& GeneWithMirror::getConstraints() const { return constraints; }

std::vector<std::shared_ptr<Gene>> GeneWithMirror::getFilledClones(const std::vector<double>& genes) {
  std::vector<std::shared_ptr<Gene>> newGenes;
  for (size_t i = 0; i < genes.size() / this->values.size(); ++i) {
    std::vector<double> tmpVals;
    for (size_t j = 0; j < this->values.size(); ++j) {
      tmpVals.push_back(genes[this->values.size() * i + j]);
    }
    newGenes.push_back(std::make_shared<GeneWithMirror>());
    newGenes.back()->setGeneValues(tmpVals);
  }
  return newGenes;
}

void GeneWithMirror::printGene() {
  std::cout << "x: " << values[0] << ", y: " << values[1] << ", phi: " << values[2] << std::endl;
}

bool GeneWithMirror::operator<(const Gene& other) const { return values < other.getGeneValues(); }