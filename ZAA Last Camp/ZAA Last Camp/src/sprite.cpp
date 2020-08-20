#include "sprite.h"

#include <vector>

//sprite class
//constructor
Sprite::Sprite() {}
Sprite::Sprite(std::vector<unsigned char> pixels, unsigned int &width, unsigned int &height) {
	this->pixels = pixels;
	this->width = width;
	this->height = height;
}

//getters
unsigned int Sprite::getWidth() {
	return width;
}
unsigned int Sprite::getHeight() {
	return height;
}
std::vector<unsigned char> Sprite::getPixels() {
	return pixels;
}

//getters RGB
int Sprite::getPixelR(const int &x, const int &y) {
	if (x < 0 || x >= width || y < 0 || y >= height) return 0;
	int xa = x * 4;
	int ya = y * 4;
	return (int)pixels[xa + ya * width];
}
int Sprite::getPixelG(const int &x, const int &y) {
	if (x < 0 || x >= width || y < 0 || y >= height) return 0;
	int xa = x * 4;
	int ya = y * 4;
	return (int)pixels[xa + ya * width + 1];
}
int Sprite::getPixelB(const int &x, const int &y) {
	if (x < 0 || x >= width || y < 0 || y >= height) return 0;
	int xa = x * 4;
	int ya = y * 4;
	return (int)pixels[xa + ya * width + 2];
}