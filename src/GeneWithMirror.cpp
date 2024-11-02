#include "GeneWithMirror.hpp"

#include "RNG.hpp"

#include <iostream>
#include <memory>
#include <vector>

GeneWithMirror::GeneWithMirror() {
  values.push_back(RNG::generate_random_double(constraints[0].first, constraints[0].second));
  values.push_back(RNG::generate_random_double(constraints[1].first, constraints[1].second));
  values.push_back(RNG::generate_random_double(constraints[2].first, constraints[2].second));
}

GeneWithMirror::GeneWithMirror(std::vector<double> values) { this->values = values; }

std::vector<double> GeneWithMirror::getGeneValues() const { return values; }

void GeneWithMirror::setGeneValues(std::vector<double> values) { this->values = values; }

const std::vector<std::pair<double, double>>& GeneWithMirror::getConstraints() const { return constraints; }

void GeneWithMirror::printGene() {
  std::cout << "x: " << values[0] << ", y: " << values[1] << ", phi: " << values[2] << std::endl;
}

bool GeneWithMirror::operator<(const Gene& other) const { return values < other.getGeneValues(); }