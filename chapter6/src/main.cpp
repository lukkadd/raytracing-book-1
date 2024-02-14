#include <iostream>
#include <fstream>
#include <cfloat>
#include <stdlib.h>
#include "sphere.hpp"
#include "hitable_list.hpp"
#include "camera.hpp"

vec3 color(const ray& r, hitable *world) {
  hit_record rec;
  if (world->hit(r,0.0, FLT_MAX, rec)) {
    return 0.5 * vec3(rec.normal.x()+1, rec.normal.y()+1,rec.normal.z()+1);
  }
  else {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
  }
}

int main (void){
  std::fstream fs;
  fs.open("./dist/image.ppm", std::fstream::out);
 
  int nx = 200;
  int ny = 100;
  int ns = 100;

  fs << "P3\n" << nx << " " << ny << "\n255\n";

  hitable *list[2];
  list[0] = new sphere(vec3(0,0,-1), 0.5);
  list[1] = new sphere(vec3(0,-100.5,-1),100);
  hitable *world = new hitable_list(list,2);

  camera cam;
  // For each frame
  for(int j = ny - 1; j >= 0; j--){
    for (int i = 0; i < nx; i++){
      vec3 col(0,0,0);
      for (int s = 0; s < ns; s++){
	float u = float(i + ((float) rand()/RAND_MAX)) / float(nx);
	float v = float(j + ((float) rand()/RAND_MAX)) / float(ny);

	ray r = cam.get_ray(u,v);

	//Calculate a color
	vec3 p = r.point_at_parameter(2.0);
	col += color(r, world);
      }
      
      col /= float(ns);

      int ir = int(255.99 * col[0]);
      int ig = int(255.99 * col[1]);
      int ib = int(255.99 * col[2]);
      
      fs << ir << " " << ig << " " << ib << "\n";
    }
  }

  fs.close();
  return 0;
}