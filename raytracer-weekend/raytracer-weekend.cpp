#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

// This is here to avoid multiple defines
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <chrono>


int main()
{
	// World
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 1280;
	cam.samples_per_pixel = 16;
	cam.max_depth = 8;

	auto start = std::chrono::high_resolution_clock::now();


	cam.render(world);

	auto end = std::chrono::high_resolution_clock::now();

	double seconds = std::chrono::duration<double>(end - start).count();

	std::cout << std::fixed << std::setprecision(3) << "Render time: " << seconds << " seconds" << std::endl;

	return 0;
}