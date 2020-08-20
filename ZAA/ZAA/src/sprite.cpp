#include <vector>

#include "sprite.h"

Sprite::Sprite(std::vector<unsigned char> &pixels, int width, int height) {
	this->pixels = pixels;
	this->width = width;
	this->height = height;
}

int Sprite::getPixelR(const int &x, const int &y) {
	if (x < 0 || x >= width || y < 0 || y >= height) return 0;
	int xa = x * 4;
	int ya = y * 4;
	return pixels[xa + ya * width];
}
int Sprite::getPixelG(const int &x, const int &y) {
	if (x < 0 || x >= width || y < 0 || y >= height) return 0;
	int xa = x * 4;
	int ya = y * 4;
	return pixels[xa + ya * width + 1];
}
int Sprite::getPixelB(const int &x, const int &y) {
	if (x < 0 || x >= width || y < 0 || y >= height) return 0;
	int xa = x * 4;
	int ya = y * 4;
	return pixels[xa + ya * width + 2];
}