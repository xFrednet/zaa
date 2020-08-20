#pragma once
#include <vector>

class Sprite {
public:
	std::vector<unsigned char> pixels;
	int width = -1;
	int height = -1;
	Sprite();
	Sprite(std::vector<unsigned char> &pixels, int width, int height);
	int getPixelR(const int &x, const int &y);
	int getPixelG(const int &x, const int &y);
	int getPixelB(const int &x, const int &y);
};
