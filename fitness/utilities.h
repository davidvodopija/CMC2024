#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>

using std::make_shared;
using std::shared_ptr;

const float inf = std::numeric_limits<float>::infinity();
const double pi = 3.1415926535897932385;

inline float degrees_to_radians(float degrees) {
  return degrees * pi / 180;
}

inline float random_float() {
  static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
  static std::mt19937 generator;
  return distribution(generator);
}

inline double random_double() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

// Returns a random real in [min, max>
inline float random_float(float min, float max) {
  return min + (max - min) * random_float();
}

// Returns a random int in [min, mnax]
inline int random_int(int min, int max) {
  return int(random_float(min, max + 1));
}

class interval {
  public:
    float min, max;

    interval() : min(+inf), max(-inf) {}  // Empty interval

    interval(float min, float max) : min(min), max(max) {}

    interval(const interval& a, const interval& b) {
      min = a.min <= b.min ? a.min : b.min;
      max = a.max >= b.max ? a.max : b.max;
    }

    float size() const {
      return max - min;
    }

    bool contains(float x) const {
      return min <= x && x <= max;
    }

    bool surrounds(float x) const {
      return min < x && x < max;
    }

    float clamp(float x) const {
      if (x < min) return min;
      if (x > max) return max;
      return x;
    }

    interval expand(float delta) const {
      float padding = delta / 2;
      return interval(min - padding, max + padding);
    }

    static const interval empty, universe;
};

const interval interval::empty = interval(+inf, -inf);
const interval interval::universe = interval(-inf, +inf);

// Shifts the interval by a given displacement
interval operator+(const interval& ival, float displacement) {
  return interval(ival.min + displacement, ival.max + displacement);
}

// Shifts the interval by a given displacement
interval operator+(float displacement, const interval& ival) {
  return ival + displacement;
}

inline interval intersection(const interval& a, const interval& b) {
  if (a.max < b.min || b.max < a.min) return interval(+inf, -inf);
  if (a.contains(b.min) && a.contains(b.max)) return b;
  if (b.contains(a.min) && b.contains(a.max)) return a;
  if (a.contains(b.min) && b.contains(a.max)) return interval(b.min, a.max);
  if (a.contains(b.max) && b.contains(a.min)) return interval(a.min, b.max);
}
#endif

#include "vec.h"
#include "ray.h"