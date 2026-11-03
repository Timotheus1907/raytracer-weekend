#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>
#include <fstream>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Quadratic formula to determine if a ray intersects a sphere
// If discriminant is greater than 0, the ray intersects the sphere
// returns value of t if ray intersects sphere, else returns -1.0
double hit_sphere(const point3& center, double radius, const ray& r) {
	vec3 oc = center - r.origin();
	auto a = r.direction().length_squared();
	auto h = dot(r.direction(), oc);
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = h * h - a * c;

	if (discriminant < 0) return -1.0;
	// This possibly can return values from behind the camera
	else return (h - std::sqrt(discriminant)) / a;
}

color ray_color(const ray& r) {
	point3 sphere_center(0, 0, -1);
	double sphere_radius = 0.5;

	auto t = hit_sphere(sphere_center, sphere_radius, r);

	if (t > 0.0) {
		// Surface Normal
		vec3 N = unit_vector(r.at(t) - sphere_center);
		return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	
	// Background color gradient
	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
	// Image

	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 1280;

	// Image Height, and ensure that it's atleast 1
	int image_height = int(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	// Png setup
	const int channels = 3;
	std::vector<unsigned char> pixels(image_width * image_height * channels);

	// Camera

	auto focal_length = 1.0;
	// Viewport widths less than one are ok
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double(image_width) / image_height); // Viewport width is scaled to the image width and height
	auto camera_center = point3(0, 0, 0);

	// Calculate the horizontal and vertical vectors of the viewport edges
	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel
	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	// Calculate the location of the upper left pixel using viewport corner and pixel delta vectors
	auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);









	// Render

	for (int j = 0; j < image_height; j++) {
		std::cout << "\rScanlines remaining: " << (image_height - 1 - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {
			auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			// Orthoganal, not unit vector
			auto ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);
			color pixel_color = ray_color(r);

			int index = (j * image_width + i) * channels;

			auto red = pixel_color.x();
			auto green = pixel_color.y();
			auto blue = pixel_color.z();
			// Divide the color by the number of samples and gamma-correct for gamma=2.0.
			int rbyte = int(255.999 * red);
			int gbyte = int(255.999 * green);
			int bbyte = int(255.999 * blue);
			
			pixels[index] = rbyte;
			pixels[index + 1] = gbyte;
			pixels[index + 2] = bbyte;
		}
	}

	const char* filename = "image.png";

	int success = stbi_write_png(filename, image_width, image_height, channels, pixels.data(), image_width * channels);

	if (success) std::cout << "\nImage Created!" << std::endl;
	else std::cout << "\nImage Creation Failed!" << std::endl;



	return 0;
}