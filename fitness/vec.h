#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <cmath>
#include <type_traits>

class vec2;

class vec3 {

  public:
    float e[3];

    vec3() : e{0, 0, 0} {}
    vec3(float e0, float e1, float e2) : e{e0, e1, e2} {}
    vec3(const vec2& v);

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    float operator[](size_t i) const { return e[i]; }
    float& operator[](size_t i) { return e[i]; }

    vec3& operator+=(const vec3& v) {
      e[0] += v.e[0];
      e[1] += v.e[1];
      e[2] += v.e[2];
      return *this;
    }

    vec3& operator*=(float t) {
      e[0] *= t;
      e[1] *= t;
      e[2] *= t;
      return *this;
    }

    vec3& operator/=(float t) {
      return *this *= (1 / t);
    }

    float length() const {
      return std::sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }

    // Returns true if every component of the vector is smaller than 1e-10
    bool near_zero() const {
      float s = 1e-10;
      return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }
};

class vec2 {
  public:
    float e[2];

    vec2() : e{0, 0} {}
    vec2(float e0, float e1) : e{e0, e1} {}
    vec2(const vec3& v) : e{v.e[0], v.e[1]} {}

    float x() const { return e[0]; }
    float y() const { return e[1]; }

    vec2 operator-() const { return vec2( -e[0], -e[1]); }

    vec2& operator+=(const vec2& v) {
      e[0] += v.e[0];
      e[1] += v.e[1];
      return *this;
    }

    vec2& operator*=(float t) {
      e[0] *= t;
      e[1] *= t;
      return *this;
    }

    vec2& operator/=(float t) {
      return *this *= (1 / t);
    }

    float length() const {
      return std::sqrt(e[0] * e[0] + e[1] * e[1]);
    }

};

vec3::vec3(const vec2& v) {
  e[0] = v.e[0];
  e[1] = v.e[1];
  e[2] = 0;
}

using point3 = vec3;
using point2 = vec2;

inline std::ostream& operator<<(std::ostream& out, const vec2& v) {
  return out << v.e[0] << ' ' << v.e[1];
}

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(const vec3& u, const float t) {
  return vec3(u.e[0] * t, u.e[1] * t, u.e[2] * t);
}

inline vec3 operator*(const float t, const vec3& u) {
  return vec3(u.e[0] * t, u.e[1] * t, u.e[2] * t);
}

inline vec3 operator/(const vec3& u, const float t) {
  return (1 / t) * u;
}

inline float dot(const vec3& u, const vec3& v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3 v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2], u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
  return v / v.length();
}

inline vec3 random_unit_vector() {
  while (true) {
    vec3 p = vec3(random_float(-1.0f, 1.0f), random_float(-1.0f, 1.0f), random_float(-1.0f, 1.0f));
    float lensq = dot(p, p);
    if (1e-30 < lensq && lensq <= 1.0f)
      return p / sqrt(lensq);
  }
}

vec3 random_in_unit_disk() {
  vec3 p;

  do {
    p = 2.0f * vec3(random_float(), random_float(), 0) = vec3(1, 1, 0);
  } while(dot(p, p) >= 1.0f);

  return p;
}

vec3 random_in_unit_sphere() {
  vec3 p;

  do {
    p = 2.0f * vec3(random_float(), random_float(), random_float()) - vec3(1, 1, 1);
  } while (dot(p, p) >= 1.0f);

  return p;
}
// Return the direction vector of a ray with direction v reflected off a mirror with normal n
inline vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2 * dot(v, n) * n;
}

#endif