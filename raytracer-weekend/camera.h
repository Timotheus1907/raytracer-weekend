#ifndef CAMERA_H
#define CAMERA_H

// Temp, stop visual studio related errors
//#include "rtweekend.h"
//

#include "hittable.h"

#include "stb_image_write.h"

#include <vector>

class camera {
public:
	double aspect_ratio = 1.0;
	int image_width = 100;


	void render(const hittable& world){
		initialize();

		// Render

		for (int j = 0; j < image_height; j++) {
			std::cout << "\rScanlines remaining: " << (image_height - 1 - j) << ' ' << std::flush;
			for (int i = 0; i < image_width; i++) {
				auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
				// Orthoganal, not unit vector
				auto ray_direction = pixel_center - center;

				ray r(center, ray_direction);

				color pixel_color = ray_color(r, world);


				int index = (j * image_width + i) * channels;

				write_color(pixels, pixel_color, index);
			}
		}

		const char* filename = "image.png";

		int success = stbi_write_png(filename, image_width, image_height, channels, pixels.data(), image_width * channels);

		if (success) std::cout << "\nImage Created!" << std::endl;
		else std::cout << "\nImage Creation Failed!" << std::endl;
	}

private:
	int image_height;
	int channels = 3;
	point3 center;
	point3 pixel00_loc;
	vec3 pixel_delta_u;
	vec3 pixel_delta_v;
	std::vector<unsigned char> pixels;

	void initialize() {
		// Image Height, and ensure that it's atleast 1
		image_height = int(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		// Png setup
		pixels.resize(image_width * image_height * channels);

		center = point3(0, 0, 0);

		// Camera

		auto focal_length = 1.0;
		// Viewport widths less than one are ok
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * (double(image_width) / image_height); // Viewport width is scaled to the image width and height

		// Calculate the horizontal and vertical vectors of the viewport edges
		auto viewport_u = vec3(viewport_width, 0, 0);
		auto viewport_v = vec3(0, -viewport_height, 0);

		// Calculate the horizontal and vertical delta vectors from pixel to pixel
		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		// Calculate the location of the upper left pixel using viewport corner and pixel delta vectors
		auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
		pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
	}

	color ray_color(const ray& r, const hittable& world) const {
		hit_record rec;
		if (world.hit(r, interval(0, infinity), rec)) {
			return 0.5 * (rec.normal + color(1, 1, 1));
		}

		// Background color gradient
		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}
};


#endif