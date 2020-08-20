#pragma once

#include <vector>

class Sprite {
protected:
	unsigned int width = 0;
	unsigned int height = 0;
	std::vector<unsigned char> pixels;
public:
	//constructor
	Sprite();
	Sprite(std::vector<unsigned char> pixels, unsigned int &width, unsigned int &height);

	//getters
	unsigned int getWidth();
	unsigned int getHeight();
	std::vector<unsigned char> getPixels();

	//getters RGB
	int getPixelR(const int &x, const int &y);
	int getPixelG(const int &x, const int &y);
	int getPixelB(const int &x, const int &y);
};
