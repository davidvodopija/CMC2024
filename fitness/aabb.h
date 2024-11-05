#ifndef AABB_H
#define AABB_H

#include "utilities.h"

#include <algorithm>

// Axis-aligned minimum bounding box
class aabb {
  public:
    interval x, y, z;

    aabb() {}

    aabb(const interval& x, const interval& y, const interval& z) : x(x), y(y), z(z) {
      pad_to_minimums();
    }

    // a and b are opposite points in a parallelepepid
    aabb(const point3& a, const point3& b) {
      x = (a[0] <= b[0]) ? interval(a[0], b[0]) : interval(b[0], a[0]);
      y = (a[1] <= b[1]) ? interval(a[1], b[1]) : interval(b[1], a[1]);
      z = (a[2] <= b[2]) ? interval(a[2], b[2]) : interval(b[2], a[2]);

      pad_to_minimums();
    }

    aabb(const aabb& box0, const aabb& box1) {
      x = interval(box0.x, box1.x);
      y = interval(box0.y, box1.y);
      z = interval(box0.z, box1.z);
    }

    // Returns the coresponding interval for a given axis (e.g. x-axis for n = 0...)
    const interval& axis_interval(size_t n) const {
      if (n == 1) return y;
      if (n == 2) return z;
      return x;
    }

    bool hit(const ray3& r, interval ray_t) const {
      const point3& ray_orig = r.origin();
      const vec3& ray_dir = r.direction();

      for (size_t axis = 0; axis < 3; axis++) {
        const interval& ax = axis_interval(axis);
        const float adinv = 1.0f / ray_dir[axis];

        float t0 = (ax.min - ray_orig[axis]) * adinv;
        float t1 = (ax.max - ray_orig[axis]) * adinv;

        if (t0 < t1) {
          if (t0 > ray_t.min) ray_t.min = t0;
          if (t1 < ray_t.max) ray_t.max = t1;
        } else {
          if (t1 > ray_t.min) ray_t.min = t1;
          if (t0 < ray_t.max) ray_t.max = t0;          
        }

        if (ray_t.max <= ray_t.min) return false;
      }

      return true;
    }

    // Returns the index of the longest axis of the bounding box
    size_t longest_axis() const {
      if (x.size() > y.size()) return x.size() > z.size() ? 0 : 2;
      else return y.size() > z.size() ? 1 : 2;
    }

    static const aabb empty, universe;

  private:
    // Adjust the AABB so that no side is narrower than some delta, padding if necessary
    void pad_to_minimums() {

      float delta = 0.0001f;
      if (x.size() < delta) x = x.expand(delta);
      if (y.size() < delta) y = y.expand(delta);
      if (z.size() < delta) z = z.expand(delta);
    }
};

const aabb aabb::empty = aabb(interval::empty, interval::empty, interval::empty);
const aabb aabb::universe = aabb(interval::universe, interval::universe, interval::universe);

aabb operator+(const aabb& bbox, const vec3& offset) {
  return aabb(bbox.x + offset.x(), bbox.y + offset.y(), bbox.z + offset.z());
}

aabb operator+(const vec3& offset, const aabb& bbox) {
  return bbox + offset;
}

#include "hittable.h"

// A container for hittable objects that can give information about potential ray-hits
class bvh_node : public hittable {
  public:
    bvh_node(hittable_list list) : bvh_node(list.objects, 0, list.objects.size()) {}

    // Build the bounding box of the span of source objects
    bvh_node(std::vector<shared_ptr<hittable>>& objects, size_t start, size_t end) {
      bbox = aabb::empty;
      for (size_t obj_index = start; obj_index < end; obj_index++) {
        bbox = aabb(bbox, objects[obj_index]->bounding_box());
      }
 
      size_t axis = bbox.longest_axis();

      auto comparator = (axis == 0) ? box_x_compare
                      : (axis == 1) ? box_y_compare
                                    : box_z_compare;

      size_t object_span = end - start;

      if (object_span == 1) {
        left = right = objects[start];
      } else if (object_span == 2) {
        left = objects[start];
        right = objects[start + 1];
      } else {
        std::sort(std::begin(objects) + start, std::begin(objects) + end, comparator);
      
        auto mid = start + object_span / 2;
        left = make_shared<bvh_node>(objects, start, mid);
        right = make_shared<bvh_node>(objects, mid, end);
      }
    }

    bool hit(const ray3& r, interval ray_t, hit_record& rec) const override {
      if (!bbox.hit(r, ray_t))
        return false;

      bool hit_left = left->hit(r, ray_t, rec);
      bool hit_right = right->hit(r, interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

      return hit_left || hit_right;
    }

    aabb bounding_box() const override { return bbox; }

  private:
    shared_ptr<hittable> left;
    shared_ptr<hittable> right;
    aabb bbox;

    static bool box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b, size_t axis) {
      interval a_axis_interval = a->bounding_box().axis_interval(axis);
      interval b_axis_interval = b->bounding_box().axis_interval(axis);
      return a_axis_interval.min < b_axis_interval.min;
    }

    static bool box_x_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
      return box_compare(a, b, 0);
    }

    static bool box_y_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
      return box_compare(a, b, 1);
    }

    static bool box_z_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
      return box_compare(a, b, 2);
    }
};

#endif