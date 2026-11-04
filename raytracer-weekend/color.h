#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <vector>

using color = vec3;

void write_color(std::vector<unsigned char>& pixels, const color& pixel_color, int index) {
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


#endif