#ifndef MYCAMERA_H
#define MYCAMERA_H

#include "hittable.h"

class myCamera {
  public:
    float aspect_ratio = 1.0f;          // Ration of image width over height
    int image_width = 1000;           // Render image width in pixel count
    size_t samples_per_pixel = 1;       // Count of random samples for each pixel
    int max_depth = 1;              // Maximum number of ray bounces into scene
    vec3 background;                    // Scene background color

    float vfov = 90;                    // Vertical view angle (field of view)
    point3 lookfrom = point3(10, 10, 10);  // Point camera is looking from
    point3 lookat = point3(10, 10, 0);   // Point camera is looking at
    vec3 vup = vec3(0, 1, 0);           // Camera-relative "up" direction

    float focus_dist = 10;              // Distance from camera lookfrom point to plane of perfect focus

    // Render image and output in std::cout
    void render(const hittable& world) {
      initialize();

      std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

      for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
          ray3 r = get_ray(i, j);
          vec3 pixel_color = ray_color(r, world);

          write_color(std::cout, pixel_color);
        }
      }
    }

    // Rendr image and 
    void render_image(const hittable& world, std::vector<unsigned int>& image_buffer) {
      initialize();

      for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
          ray3 r = get_ray(i, j);
          vec3 pixel_color = ray_color(r, world);
          unsigned int clr;

          static const interval intensity(0.000f, 0.999f);
          unsigned int r_byte = (unsigned int)(256 * intensity.clamp(pixel_color.x()));
          unsigned int g_byte = (unsigned int)(256 * intensity.clamp(pixel_color.y()));
          unsigned int b_byte = (unsigned int)(256 * intensity.clamp(pixel_color.z()));

          clr = (r_byte << 16) + (g_byte << 8) + b_byte;
          image_buffer[image_width * j + i] = clr;
        }
      }
    }

    // Image buffer to std::cout ppm image
    void image_to_ppm(const std::vector<unsigned int>& image_buffer) {
      std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

      for (size_t i = 0; i < image_width * image_height; i++) {
        unsigned int clr = image_buffer[i];

        std::cout << ((clr >> 16) & 0x000000FF) << ' ' << ((clr >> 8) & 0x000000FF)  << ' ' << (clr & 0x000000FF) << '\n';
      }
    }

    inline int get_image_height() const { return image_height; }

  private:
    int image_height;                // Render image height
    point3 center;                      // Camera center
    point3 pixel00_loc;                 // Location of pixel 0, 0
    vec3 pixel_delta_u;                 // Offset to pixel to the right
    vec3 pixel_delta_v;                 // Offset to pixel below
    vec3 u, v, w;                       // Camera frame basis vectors

    void initialize() {
      image_height = int(image_width / aspect_ratio);
      image_height = (image_height < 1) ? 1 : image_height;

      center = lookfrom;

      // Determine viewport dimensions
      float theta = degrees_to_radians(vfov);
      float h = tan(theta / 2);
      float viewport_height = 2 * h * focus_dist;
      float viewport_width = viewport_height * (float(image_width) / image_height);

      // Calculate the u, v, w basis vctors for the camera coordinate frame
      w = unit_vector(lookfrom - lookat);
      u = unit_vector(cross(vup, w));
      v = cross(w, u);

      // Calculate the vectors across the horizontal and down the vectical viewport edges
      vec3 viewport_u = viewport_width * u;
      vec3 viewport_v = viewport_height * -v;

      // Calculate the horizontal and vertical delta vectors from pizel to pixel
      pixel_delta_u = viewport_u / image_width;
      pixel_delta_v = viewport_v / image_height;

      // Calculate the location of the upper left pixel
      vec3 viewport_upper_left = center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
      pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);
    }

    // Construct a camera ray originating from the defocus disk and directred at a randomly
    // sampled point around the pixel location i, j
    ray3 get_ray(int i, int j) const {
      vec3 pixel_sample = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      vec3 ray_direction = pixel_sample - center;
      
      return ray3(center, ray_direction);
    }

    vec3 ray_color(const ray3& r, const hittable& world) const {
      hit_record rec;
      if (!world.hit(r, interval(0.001f, inf), rec)) return background;

      return rec.color;
    }

    void write_color(std::ostream& out, const vec3& pixel_color) {
      static const interval intensity(0.000f, 0.999f);
      int r_byte = int(256 * intensity.clamp(pixel_color.x()));
      int g_byte = int(256 * intensity.clamp(pixel_color.y()));
      int b_byte = int(256 * intensity.clamp(pixel_color.z()));

      out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
    }
};

#endif