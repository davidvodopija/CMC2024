#ifndef RAY_H
#define RAY_H

#include "vec.h"

class ray3 {
  public:
    ray3() {}

    ray3(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    const point3 origin() const { return orig; }
    const vec3& direction() const { return dir; }

    point3 at(double t) const {
      return orig + t * dir;
    }

    private:
      point3 orig;
      vec3 dir;
};

class ray2 {
  public:
    ray2() {}

    ray2(const point2& origin, const vec2& direction) : orig(origin), dir(direction) {
      if (direction.e[0] == 0 && direction.e[1] == 0) {
        throw std::invalid_argument("Direction is a null vector.");
      } else if (direction.e[0] == 0) { // Vertical line
        k = inf; l = inf;
      } else if (direction.e[1] == 0) { // Horizontal line
        k = 0; l = origin.e[1];
      } else {
        k = direction.e[1] / direction.e[0]; l = origin.e[1] - k * origin.e[0];
      }
    }

    // k - slope, l - y-axis intersection, x0 - 
    ray2(double k, double l, double x0 = 0) : k(k), l(l) {
      if ((k == inf || k == -inf) && (l == inf || l == -inf)) { // Vertical line
        dir = vec2(0, 1); orig = point2(x0, 0);
      } else if (k == 0) { // Horizontal line
        dir = vec2(1, 0); orig = point2(0, l);
      } else {
        dir = vec2(1, k); orig = point2(0, l);
      }
    }

    const point2 origin() const { return orig; }
    const vec2& direction() const { return dir; }
    double slope() const { return k; }
    double shift() const { return l; }

    point2 at(double t) const {
      return orig + t * dir;
    }

    double y(double x) const {
       if ((k == inf || k == -inf) && (l == inf || l == -inf)) { // Vertical line
        throw std::invalid_argument("Cannot determine y value of a vertical line.");
       }
      return k * x + l;
    }

    double x(double y) const {  // Horizontal line
      if (k == 0) {
        throw std::invalid_argument("Cannot determine x value of a horizontal line.");
      } else if ((k == inf || k == -inf) && (l == inf || l == -inf)) {
        return orig.e[0];
      }
      return (y - l) / k;
    }

    private:
      point2 orig;
      vec2 dir;
      double k, l;
};

#endif