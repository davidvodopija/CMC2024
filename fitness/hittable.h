#ifndef HITTABLE_H
#define HITTABLE_H

#include "aabb.h"
#include "utilities.h"

#include <vector>

class material;
//class aabb;

// Struct class for information about ray-object intersection
class hit_record {
  public:
    point3 p;         // point of intersection
    vec3 normal;      // Normal of the intersection plane
    bool front_face;
    float t, u, v;
    vec3 color;

    void set_face_normal(const ray3& r, const vec3& outward_normal) {
      front_face = dot(r.direction(), outward_normal) < 0;
      normal = front_face ? outward_normal : -outward_normal;
    }
};

// Abstract class of an object that can interfere with a ray
class hittable {
  public:
    virtual ~hittable() = default;

    virtual bool hit(const ray3& r, interval ray_t, hit_record& rec) const = 0;

    virtual aabb bounding_box() const = 0;
};

// A list of hittable objects, can be considered the world
class hittable_list : public hittable {
  public:
    std::vector<shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<hittable> object) {
      objects.push_back(object);
      bbox = aabb(bbox, object->bounding_box());
    }

    bool hit(const ray3& r, interval ray_t, hit_record& rec) const override {
      hit_record temp_rec;
      bool hit_anything = false;
      float closest_so_far = ray_t.max;

      for (auto obj = objects.begin(); obj != objects.end(); obj++) {
        if ((*obj)->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
          hit_anything = true;
          closest_so_far = temp_rec.t;
          rec = temp_rec;
        }
      }

      return hit_anything;
    }

    aabb bounding_box() const override { return bbox; }
    
  private:
    aabb bbox;
}; 

// Concrete realizations of hittable objects
void get_sphere_uv(const vec3& p, float& u, float& v) {
  float phi = std::atan2(-p.z(), p.x()) + pi;
  float theta = std::acos(-p.y());

  u = phi / (2 * pi);
  v = theta / pi;
}

// A sphere
class sphere : public hittable {
  public:
    point3 center;
    float radius;
    vec3 color;
    aabb bbox;

    sphere() {}
    sphere(vec3 center, float radius, const vec3& color) : center(center), radius(radius), color(color) {
      vec3 r_vec = vec3(radius, radius, radius);
      bbox = aabb(center - r_vec, center + r_vec);
    }

    bool hit(const ray3& r, interval ray_t, hit_record& rec) const override {
      vec3 oc = center - r.origin();
      float a = dot(r.direction(), r.direction());
      float h = dot(oc, r.direction());
      float c = dot(oc, oc) - radius * radius;
      float discriminant = h * h - a * c;

      if (discriminant < 0.0f) return false;

      float sqrtd = std::sqrt(discriminant);
      float root = (h - sqrtd) / a;

      if (!ray_t.surrounds(root)) {
        root = (h + sqrtd) / a;
        if (!ray_t.surrounds(root)) return false;
      }

      rec.t = root;
      rec.p = r.at(rec.t);
      vec3 outward_normal = (rec.p - center) / radius;
      rec.set_face_normal(r, outward_normal);
      get_sphere_uv(outward_normal, rec.u, rec.v);
      rec.color = color;

      return true;
    }

    aabb bounding_box() const override { return bbox; }
};


// A quadrilateral
class quad : public hittable {
  public:
    quad(const point3& Q, const vec3& u, const vec3& v, const vec3& color): Q(Q), u(u), v(v), color(color) {
      
      vec3 n = cross(u, v);
      normal = unit_vector(n);
      D = dot(normal, Q);
      w = n / dot(n, n);

      set_bounding_box();
    }

    // Compute the bounding box of all four vertices
    void set_bounding_box() {
      aabb bbox_diagonal1 = aabb(Q, Q + u + v);
      aabb bbox_diagonal2 = aabb(Q + u, Q + v);
      bbox = aabb(bbox_diagonal1, bbox_diagonal2);
    }

    aabb bounding_box() const override { return bbox; }

    bool hit(const ray3& r, interval ray_t, hit_record& rec) const override {
      float denom = dot(normal, r.direction());

      // No hit if the ray is parallel to the plane
      if (std::fabs(denom) < 1e-8)
        return false;

      // Return false if the hit point parameter t is outside the ray interval
      float t = (D - dot(normal, r.origin())) / denom;
      if (!ray_t.contains(t))
        return false;

      // Determine if the git point lies within the planar shape using its plane coordinates
      point3 intersection = r.at(t);
      vec3 plaanr_hitpt_vector = intersection - Q;
      float alpha = dot(w, cross(plaanr_hitpt_vector, v));
      float beta = dot(w, cross(u, plaanr_hitpt_vector));

      if (!is_interior(alpha, beta, rec))
        return false;

      // Ray hits the 2D shape; set the rest of the hitrecord and return true
      rec.t = t;
      rec.p = intersection;
      rec.color = color;
      rec.set_face_normal(r, normal);

      return true;
    }

    // Given a point in plane coordinates, return false if it is outside of primitive, otherwise true
    virtual bool is_interior(float a, float b, hit_record& rec) const {
      interval unit_interval = interval(0, 1);

      if (!unit_interval.contains(a) || !unit_interval.contains(b))
        return false;

      return true;
    }

  private:
    // Plane equation: Ax + By + Cz = D
    point3 Q;
    vec3 u, v, w, normal;
    float D;
    aabb bbox;
    vec3 color;
};

class disk : public hittable {
  public:
    disk(const point3& center, const vec3& u, const vec3& v, float radius, const vec3& color) 
      : center(center), u(unit_vector(u)), v(unit_vector(v)), radius(radius), color(color) {
      vec3 n = cross(this->u, this->v);
      normal = unit_vector(n);
      D = dot(normal, center);
      w = n / dot(n, n);

      set_bounding_box();
    }

    void set_bounding_box() {
      aabb bbox_diagonal1 = aabb(center - radius * u - radius * v, center + radius * u + radius * v);
      aabb bbox_diagonal2 = aabb(center - radius * v, center - radius * u);
      bbox = aabb(bbox_diagonal1, bbox_diagonal2);
    }

    bool hit(const ray3& r, interval ray_t, hit_record& rec) const override {
      float denom = dot(normal, r.direction());

      if (std::fabs(denom) < 1e-08) return false;

      float t = (D - dot(normal, r.origin())) / denom;
      if (!ray_t.contains(t)) return false;

      point3 intersection = r.at(t);
      vec3 plaanr_hitpt_vector = intersection - center;
      float alpha = dot(w, cross(plaanr_hitpt_vector, v));
      float beta = dot(w, cross(u, plaanr_hitpt_vector));

      if (!is_interior(alpha, beta, rec)) return false;

      rec.t = t;
      rec.p = intersection;
      rec.color = color;
      rec.set_face_normal(r, normal);

      return true;
    }

    aabb bounding_box() const override { return bbox; }

  private:
    point3 center;
    vec3 u, v, w, normal;
    float D, radius;
    aabb bbox;
    vec3 color;

    bool is_interior(float a, float b, hit_record& rec) const {
      if (std::sqrt(a * a + b * b + 2 * a * b * dot(u, v)) < radius) return true;

      return false;
    }
};

// Return the 3D box (six sides) that contains the two opposite vertices a and b
inline shared_ptr<hittable_list> box(const point3& a, const point3& b, const vec3& color) {
  shared_ptr<hittable_list> sides = make_shared<hittable_list>();

  // construct the two opposite vertices with the minimum and maximum coordinates
  point3 min = point3(std::fmin(a.x(), b.x()), std::fmin(a.y(), b.y()), std::fmin(a.z(), b.z()));
  point3 max = point3(std::fmax(a.x(), b.x()), std::fmax(a.y(), b.y()), std::fmax(a.z(), b.z()));

  vec3 dx = vec3(max.x() - min.x(), 0, 0);
  vec3 dy = vec3(0, max.y() - min.y(), 0);
  vec3 dz = vec3(0, 0, max.z() - min.z());

  sides->add(make_shared<quad>(point3(min.x(), min.y(), max.z()), dx, dy, color));   // front
  sides->add(make_shared<quad>(point3(max.x(), min.y(), max.z()), -dz, dy, color));   // right
  sides->add(make_shared<quad>(point3(max.x(), min.y(), min.z()), -dx, dy, color));   // back
  sides->add(make_shared<quad>(point3(min.x(), min.y(), min.z()), dz, dy, color));   // left
  sides->add(make_shared<quad>(point3(min.x(), max.y(), max.z()), dx, -dz, color));   // top
  sides->add(make_shared<quad>(point3(min.x(), min.y(), min.z()), dx, dz, color));   // bottom

  return sides;
}

class xy_rect : public hittable {
  public:
    float x0, x1, y0, y1, k;
    vec3 color;
    aabb bbox;

    xy_rect() {}
    xy_rect(float x0, float x1, float y0, float y1, float k, const vec3& color) : x0(x0), x1(x1), y0(y0), y1(y1), k(k), color(color) {
        bbox = aabb(vec3(x0, y0, k - 0.0001f), vec3(x1, y1, k + 0.0001f));
    }

    aabb bounding_box() const override { return bbox; }

    bool hit(const ray3& r, interval ray_t, hit_record& rec) const override {
      float t = (k - r.origin().z()) / r.direction().z();

      if (!ray_t.contains(t)) return false;

      float x = r.origin().x() + t * r.direction().x();
      float y = r.origin().y() + t * r.direction().y();

      if (x < x0 || x > x1 || y < y0 || y > y1) return false;

      rec.u = (x - x0) / (x1 - x0);
      rec.v = (y - y0) / (y1 - y0);
      rec.t = t;
      rec.color = color;
      rec.p = r.at(t);
      rec.set_face_normal(r, vec3(0, 0, 1));

      return true;
    }
};

class xz_rect : public hittable {
  public:
    float x0, x1, z0, z1, k;
    vec3 color;
    aabb bbox;

    xz_rect() {}
    xz_rect(float x0, float x1, float z0, float z1, float k, const vec3& color) : x0(x0), x1(x1), z0(z0), z1(z1), k(k), color(color) {
        bbox = aabb(vec3(x0, k - 0.0001f, z0), vec3(x1, k + 0.0001f, z1));
    }

    aabb bounding_box() const override { return bbox; }

    bool hit(const ray3& r, interval ray_t, hit_record& rec) const override {
      float t = (k - r.origin().y()) / r.direction().y();

      if (!ray_t.contains(t)) return false;

      float x = r.origin().x() + t * r.direction().x();
      float z = r.origin().z() + t * r.direction().z();

      if (x < x0 || x > x1 || z < z0 || z > z1) return false;

      rec.u = (x - x0) / (x1 - x0);
      rec.v = (z - z0) / (z1 - z0);
      rec.t = t;
      rec.color = color;
      rec.p = r.at(t);
      rec.set_face_normal(r, vec3(0, 1, 0));

      return true;
    }
};

class yz_rect : public hittable {
  public:
    float y0, y1, z0, z1, k;
    vec3 color;
    aabb bbox;

    yz_rect() {}
    yz_rect(float y0, float y1, float z0, float z1, float k, const vec3& color) : y0(y0), y1(y1), z0(z0), z1(z1), k(k), color(color) {
        bbox = aabb(vec3(k - 0.0001f, y0, z0), vec3(k + 0.0001f, y1, z1));
    }

    aabb bounding_box() const override { return bbox; }

    bool hit(const ray3& r, interval ray_t, hit_record& rec) const override {
      float t = (k - r.origin().x()) / r.direction().x();

      if (!ray_t.contains(t)) return false;

      float y = r.origin().y() + t * r.direction().y();
      float z = r.origin().z() + t * r.direction().z();

      if (y < y0 || y > y1 || z < z0 || z > z1) return false;

      rec.u = (y - y0) / (y1 - y0);
      rec.v = (z - z0) / (z1 - z0);
      rec.t = t;
      rec.color = color;
      rec.p = r.at(t);
      rec.set_face_normal(r, vec3(1, 0, 0));

      return true;
    }
};

// Translation of a hittable object by a given offset
class translate : public hittable {
  public:
    translate(shared_ptr<hittable> object, const vec3& offset) : object(object), offset(offset) {
      bbox = object->bounding_box() + offset;
    }

    bool hit(const ray3& r, interval ray_t, hit_record& rec) const override {
      ray3 offset_r(r.origin() - offset, r.direction());

      if (!object->hit(offset_r, ray_t, rec))
        return false;

      rec.p += offset;

      return true;
    }

    aabb bounding_box() const override { return bbox; }

  private:
    shared_ptr<hittable> object;
    vec3 offset;
    aabb bbox;
};

class rotate_y : public hittable {
  public:

    rotate_y(shared_ptr<hittable> object, float angle) : object(object) {
      float radians = degrees_to_radians(angle);

      sin_theta = std::sin(radians);
      cos_theta = std::cos(radians);
      bbox = object->bounding_box();

      point3 min(inf, inf, inf);
      point3 max(-inf, -inf, -inf);

      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          for (int k = 0; k < 2; k++) {
            float x = i * bbox.x.max + (1 - i) * bbox.x.min;
            float y = j * bbox.y.max + (1 - j) * bbox.y.min;
            float z = k * bbox.z.max + (1 - k) * bbox.z.min;

            float new_x = cos_theta * x + sin_theta * z;
            float new_z = -sin_theta * x + cos_theta * z;

            vec3 tester(new_x, y, new_z);

            for (int c = 0; c < 3; c++) {
              min[c] = std::fmin(min[c], tester[c]);
              max[c] = std::fmax(max[c], tester[c]); 
            }
          }
        }
      }

      bbox = aabb(min, max);
    }

    bool hit(const ray3& r, interval ray_t, hit_record& rec) const override {

      // Translate the ray from world space to object space
      point3 origin = point3(
            (cos_theta * r.origin().x()) - (sin_theta * r.origin().z()),
            r.origin().y(),
            (sin_theta * r.origin().x()) + (cos_theta * r.origin().z())
      );

      point3 direction = point3(
            (cos_theta * r.direction().x()) - (sin_theta * r.direction().z()),
            r.direction().y(),
            (sin_theta * r.direction().x()) + (cos_theta * r.direction().z())
      );

      ray3 rotated_r(origin, direction);

      // Determine whether an intersection axists in object space
      if (!object->hit(rotated_r, ray_t, rec))
        return false;

      // Transform the intersection from object space back to world space
      rec.p = point3(
            (cos_theta * rec.p.x()) + (sin_theta * rec.p.z()),
            rec.p.y(),
            (-sin_theta * rec.p.x()) + (cos_theta * rec.p.z())
      );

      rec.normal = vec3(
            (cos_theta * rec.normal.x()) + (sin_theta * rec.normal.z()),
            rec.normal.y(),
            (-sin_theta * rec.normal.x()) + (cos_theta * rec.normal.z())
      );

      return true;
    }

    aabb bounding_box() const override { return bbox; }

  private:
    shared_ptr<hittable> object;
    float sin_theta, cos_theta;
    aabb bbox;
};

#endif