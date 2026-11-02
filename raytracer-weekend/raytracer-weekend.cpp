#include "color.h"
#include "vec3.h"

#include <iostream>
#include <fstream>

int main()
{
	// Image

	int image_width = 256;
	int image_height = 256;

	// Render

	std::ofstream file;
	file.open("image.ppm");

	// PPM Image Formatting
	file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++) {
		std::cout << "\rScanlines remaining: " << (image_height - 1 - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {
			auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
			write_color(file, pixel_color);
		}
	}

	file.close();

	std::cout << "\nImage Created!" << std::endl;

	return 0;
}