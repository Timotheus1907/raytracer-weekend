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
		std::cout << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {
			auto r = double(i) / (image_width - 1);
			auto g = double(j) / (image_height - 1);
			auto b = 0.0;

			int ir = int(255.999 * r);
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);

			file << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}

	file.close();

	std::cout << "\nImage Created!" << std::endl;

	return 0;
}