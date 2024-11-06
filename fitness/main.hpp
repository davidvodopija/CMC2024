#ifndef KURAC
#define KURAC

#include "aabb.h"
#include "myCam.h"
#include "utilities.h"

#include <fstream>
#include <iostream>

#define TEMPLE_1000 "fitness/temple_1000.txt"
#define TEMPLE_2000 "fitness/temple_2000.txt"
#define TEMPLE_3000 "fitness/temple_3000.txt"

const float white_percentage = 0.68f;
const unsigned int IMAGE_WIDTH = 1000;

// Temple geometry
const bool temple_array[20][20] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                   {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
                                   {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
                                   {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                   {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                                   {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                   {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                                   {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                                   {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                   {1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1},
                                   {1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1},
                                   {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                   {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                                   {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                                   {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                   {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                                   {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                   {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
                                   {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
                                   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// Temple object
hittable_list temple, temple3D;
std::vector<unsigned int> temple_image(IMAGE_WIDTH* IMAGE_WIDTH);

// Camera object
myCamera cam;

// Colors
const vec3 black(0, 0, 0);
const vec3 red(1, 0, 0);
const vec3 green(0, 1, 0);

// Initialize the temple geometry
void temple_init() {
  // Border
  temple.add(make_shared<quad>(point3(0, 0, 0), vec3(20, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(0, 1, 0), vec3(1, 0, 0), vec3(0, 18, 0), black));
  temple.add(make_shared<quad>(point3(0, 19, 0), vec3(20, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(19, 1, 0), vec3(1, 0, 0), vec3(0, 18, 0), black));
  // 1
  temple.add(make_shared<quad>(point3(1, 5, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(1, 14, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  // 2
  temple.add(make_shared<quad>(point3(2, 9, 0), vec3(1, 0, 0), vec3(0, 2, 0), black));
  // 3
  temple.add(make_shared<quad>(point3(3, 4, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(3, 15, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  // 4
  temple.add(make_shared<quad>(point3(4, 6, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(4, 13, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  // 5
  temple.add(make_shared<quad>(point3(5, 1, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(5, 18, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(5, 9, 0), vec3(2, 0, 0), vec3(0, 2, 0), black));
  // 6
  temple.add(make_shared<quad>(point3(6, 3, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(6, 16, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  // 7
  temple.add(make_shared<quad>(point3(7, 7, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(7, 12, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  // 8
  temple.add(make_shared<quad>(point3(8, 2, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(8, 17, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  // 9, 10
  temple.add(make_shared<quad>(point3(9, 4, 0), vec3(2, 0, 0), vec3(0, 2, 0), black));
  temple.add(make_shared<quad>(point3(9, 14, 0), vec3(2, 0, 0), vec3(0, 2, 0), black));
  temple.add(make_shared<quad>(point3(9, 8, 0), vec3(2, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(9, 11, 0), vec3(2, 0, 0), vec3(0, 1, 0), black));
  // 11
  temple.add(make_shared<quad>(point3(11, 2, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(11, 17, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  // 12
  temple.add(make_shared<quad>(point3(12, 7, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(12, 12, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  // 13
  temple.add(make_shared<quad>(point3(13, 3, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(13, 16, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(13, 9, 0), vec3(2, 0, 0), vec3(0, 2, 0), black));
  // 14
  temple.add(make_shared<quad>(point3(14, 1, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(14, 18, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  // 15
  temple.add(make_shared<quad>(point3(15, 6, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(15, 13, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  // 16
  temple.add(make_shared<quad>(point3(16, 4, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(16, 15, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  // 17
  temple.add(make_shared<quad>(point3(17, 9, 0), vec3(1, 0, 0), vec3(0, 2, 0), black));
  // 18
  temple.add(make_shared<quad>(point3(18, 5, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));
  temple.add(make_shared<quad>(point3(18, 14, 0), vec3(1, 0, 0), vec3(0, 1, 0), black));

  temple = hittable_list(make_shared<bvh_node>(temple));

  cam.render_image(temple, temple_image);
  for (size_t i = 0; i < IMAGE_WIDTH * IMAGE_WIDTH; i++) {
    std::cout << temple_image[i] << '\n';
  }

  // cam.image_to_ppm(temple_image);
  // cam.render(temple);
}

// Load temple vector from file
void load_temple_vector(const std::string& filename) {
  std::ifstream in(filename);

  std::string line;
  size_t i = 0;

  while (getline(in, line)) {
    temple_image[i++] = std::stoul(line);
    // if (i % 1000000 == 0) std::cerr << temple_image[i] << '\n';
  }

  in.close();

  // std::cerr << "Loaded temple_img vec size: " << temple_image.size() << '\n';
}

// Initialize inner temple walls
void temple3D_init() {
  hittable_list boxes;
  // Border
  boxes.add(box(point3(0, 0, -0.25f), point3(20, 1, 0.25f), black));
  boxes.add(box(point3(0, 1, -0.25f), point3(1, 19, 0.25f), black));
  boxes.add(box(point3(0, 19, -0.25f), point3(20, 20, 0.25f), black));
  boxes.add(box(point3(19, 1, -0.25f), point3(20, 19, 0.25f), black));

  boxes.add(box(point3(1, 5, -0.25f), point3(2, 6, 0.25f), black));
  boxes.add(box(point3(1, 14, -0.25f), point3(2, 15, 0.25f), black));

  boxes.add(box(point3(2, 9, -0.25f), point3(3, 11, 0.25f), black));

  boxes.add(box(point3(3, 4, -0.25f), point3(4, 5, 0.25f), black));
  boxes.add(box(point3(3, 15, -0.25f), point3(4, 16, 0.25f), black));

  boxes.add(box(point3(4, 6, -0.25f), point3(5, 7, 0.25f), black));
  boxes.add(box(point3(4, 13, -0.25f), point3(5, 14, 0.25f), black));

  boxes.add(box(point3(5, 1, -0.25f), point3(6, 2, 0.25f), black));
  boxes.add(box(point3(5, 18, -0.25f), point3(6, 19, 0.25f), black));
  boxes.add(box(point3(5, 9, -0.25f), point3(7, 11, 0.25f), black));

  boxes.add(box(point3(6, 3, -0.25f), point3(7, 4, 0.25f), black));
  boxes.add(box(point3(6, 16, -0.25f), point3(7, 17, 0.25f), black));

  boxes.add(box(point3(7, 7, -0.25f), point3(8, 8, 0.25f), black));
  boxes.add(box(point3(7, 12, -0.25f), point3(8, 13, 0.25f), black));

  boxes.add(box(point3(8, 2, -0.25f), point3(9, 3, 0.25f), black));
  boxes.add(box(point3(8, 17, -0.25f), point3(9, 18, 0.25f), black));

  boxes.add(box(point3(9, 4, -0.25f), point3(11, 6, 0.25f), black));
  boxes.add(box(point3(9, 14, -0.25f), point3(11, 16, 0.25f), black));
  boxes.add(box(point3(9, 8, -0.25f), point3(11, 9, 0.25f), black));
  boxes.add(box(point3(9, 11, -0.25f), point3(11, 12, 0.25f), black));

  boxes.add(box(point3(11, 2, -0.25f), point3(12, 3, 0.25f), black));
  boxes.add(box(point3(11, 17, -0.25f), point3(12, 18, 0.25f), black));

  boxes.add(box(point3(12, 7, -0.25f), point3(13, 8, 0.25f), black));
  boxes.add(box(point3(12, 12, -0.25f), point3(13, 13, 0.25f), black));

  boxes.add(box(point3(13, 3, -0.25f), point3(14, 4, 0.25f), black));
  boxes.add(box(point3(13, 16, -0.25f), point3(14, 17, 0.25f), black));
  boxes.add(box(point3(13, 9, -0.25f), point3(15, 11, 0.25f), black));

  boxes.add(box(point3(14, 1, -0.25f), point3(15, 2, 0.25f), black));
  boxes.add(box(point3(14, 18, -0.25f), point3(15, 19, 0.25f), black));

  boxes.add(box(point3(15, 6, -0.25f), point3(16, 7, 0.25f), black));
  boxes.add(box(point3(15, 13, -0.25f), point3(16, 14, 0.25f), black));

  boxes.add(box(point3(16, 4, -0.25f), point3(17, 5, 0.25f), black));
  boxes.add(box(point3(16, 15, -0.25f), point3(17, 16, 0.25f), black));

  boxes.add(box(point3(17, 9, -0.25f), point3(18, 11, 0.25f), black));

  boxes.add(box(point3(18, 5, -0.25f), point3(19, 6, 0.25f), black));
  boxes.add(box(point3(18, 14, -0.25f), point3(19, 15, 0.25f), black));

  temple3D = hittable_list(make_shared<bvh_node>(boxes));
}

// Initialize the camera
void camera_init() {
  cam.image_width = IMAGE_WIDTH;
  cam.background = vec3(1, 1, 1);
}

// Returns the score
float evaluate_fitness(const float solution[]) {
  // Check if solution is valid
  int light_x = std::floor(solution[0]);
  int light_y = std::floor(solution[1]);

  // Is the light source inside a block?
  if (temple_array[19 - light_y][light_x]) {
    // std::cerr << "Light source inside block!\n";
    return 0.0f;
  }

  // Construct a world with mirrors only
  vec3 z_side = vec3(0, 0, 0.5f);

  hittable_list mirrors;  // World with only mirrors
  mirrors.add(make_shared<quad>(point3(solution[3], solution[4], -0.25f),
                                z_side,
                                0.5f * vec3(std::cos(solution[5]), std::sin(solution[5]), 0),
                                green));

  // Check first mirror
  hit_record rec;
  point3 orig = point3(solution[3], solution[4], 0.0f);
  vec3 dir = vec3(std::cos(solution[5]), std::sin(solution[5]), 0);
  int mirr_x = std::floor(solution[3]);
  int mirr_y = std::floor(solution[4]);
  if (temple3D.hit(ray3(orig, dir), interval(0.0001f, 0.5f), rec) || temple_array[19 - mirr_y][mirr_x]) {
    // std::cerr << "Mirror in collision with block!\n";
    return 0.0f;
  }

  // Check the rest and construct mirror-only world
  for (int i = 2; i < 9; i++) {
    // Check collisions
    orig = point3(solution[3 * i], solution[3 * i + 1], 0.0f);
    dir = vec3(std::cos(solution[3 * i + 2]), std::sin(solution[3 * i + 2]), 0);

    mirr_x = std::floor(solution[3 * i]);
    mirr_y = std::floor(solution[3 * i + 1]);
    if (temple3D.hit(ray3(orig, dir), interval(0.0001f, 0.5f), rec) || temple_array[19 - mirr_y][mirr_x]) {
      // std::cerr << "Mirror in collision with block!\n";
      return 0.0f;
    }
    if (mirrors.hit(ray3(orig, dir), interval(0.0001f, 0.5f), rec)) {
      // std::cerr << "Mirror in collision with mirror!\n";
      return 0.0f;
    }
    // Put in world
    mirrors.add(make_shared<quad>(point3(solution[3 * i], solution[3 * i + 1], -0.25f),
                                  z_side,
                                  0.5f * vec3(std::cos(solution[3 * i + 2]), std::sin(solution[3 * i + 2]), 0.0f),
                                  green));
  }

  // Use a bounding volume hierarchy for optimization
  mirrors = hittable_list(make_shared<bvh_node>(mirrors));

  // ************ Solution is valid, calculate score ************
  // std::cerr << "Solution valid. Calculating area...\n";

  // Construct a world with only light;  t.max = 28
  hittable_list light;

  int bounce_num = 0;  // Number of light bounces

  orig = point3(solution[0], solution[1], 0);
  dir = vec3(std::cos(solution[2]), std::sin(solution[2]), 0.0f);
  ray3 r(orig, dir);
  hit_record rec_m, rec_t;
  bool hit_mirror, hit_wall;
  interval ray_i(0.001f, 28.f);

  vec3 x_unit(1, 0, 0), y_unit(0, 1, 0), z_unit(0, 0, 1);

  do {
    // Disk around source
    light.add(make_shared<disk>(r.origin(), x_unit, y_unit, 1.0f, red));

    hit_mirror = mirrors.hit(r, ray_i, rec_m);
    hit_wall = temple3D.hit(r, ray_i, rec_t);

    vec3 u, v;

    if (hit_mirror && rec_m.t < rec_t.t) {  // Hit mirror first
      bounce_num++;

      v = rec_m.p - r.origin();
      u = unit_vector(cross(v, z_unit));
      light.add(make_shared<quad>(r.origin() - u, 2.0f * u, v, red));

      r = ray3(rec_m.p, reflect(unit_vector(r.direction()), rec_m.normal));
    }
    else {  // Didn't hit mirror or wall hit first
      v = rec_t.p - r.origin();
      u = unit_vector(cross(v, z_unit));
      light.add(make_shared<quad>(r.origin() - u, 2.0f * u, v, red));

      break;
    }

  } while (rec_m.t < rec_t.t);

  // Disk around finishing point and bvh
  light.add(make_shared<disk>(rec_t.p, x_unit, y_unit, 1.0f, red));
  light = hittable_list(make_shared<bvh_node>(light));

  // Overlay the temple image over light image and count red pixels
  std::vector<unsigned int> light_image(IMAGE_WIDTH * IMAGE_WIDTH);
  cam.render_image(light, light_image);
  // cam.image_to_ppm(light_image);

  unsigned int red_count = 0;

  for (size_t i = 0; i < IMAGE_WIDTH * IMAGE_WIDTH; i++) {
    unsigned int clr = light_image[i] & temple_image[i];
    light_image[i] = clr;
    if (clr == 0x00FF0000) red_count++;
  }

  // Calculate area and final score
  float score = float(red_count) / (white_percentage * IMAGE_WIDTH * IMAGE_WIDTH) * 100;
  // std::cerr << "Red pixels: " << red_count << '\n';
  // std::cerr << "Score: " << score << '\n';
  // cam.image_to_ppm(light_image);
  return score;
}

double start_eval(const std::vector<float>& values) {
  camera_init();
  // temple_init();
  load_temple_vector(TEMPLE_1000);
  temple3D_init();
  // std::cerr << "Temple initialized!\n";
  float sol[27];
  std::transform(values.begin(), values.end(), sol, [](float val) { return val; });
  // const double* a = &values[0];
  /*  float sol[27] = {5.0f,  5.0f, 0.26f, 11.5f, 6.5f, 0.9f,  11.9f, 16.5f, 0.95f, 15.2f,  17.6f, 2.45f, 13.8f, 12.0f,
                    0.92f, 1.6f, 6.2f,  2.53f, 2.2f, 14.7f, 0.7f,  8.5f,  14.2f, 2.325f, 8.7f,  3.05f, 2.525f}; */

  return evaluate_fitness(sol);
}

#endif