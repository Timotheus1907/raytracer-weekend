#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

#include <vector>

using color = vec3;

void write_color(std::vector<unsigned char>& pixels, const color& pixel_color, int index) {
	auto red = pixel_color.x();
	auto green = pixel_color.y();
	auto blue = pixel_color.z();
	// Divide the color by the number of samples
	// Translate the color to [0,255] range
	static const interval intensity(0.0, 0.999);
	int rbyte = int(256 * intensity.clamp(red));
	int gbyte = int(256 * intensity.clamp(green));
	int bbyte = int(256 * intensity.clamp(blue));

	pixels[index] = rbyte;
	pixels[index + 1] = gbyte;
	pixels[index + 2] = bbyte;
}


#endif