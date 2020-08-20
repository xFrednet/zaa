#include "spriteTile.h"
#include "sprite.h"

//constructor
SpriteTile::SpriteTile() {}
SpriteTile::SpriteTile(unsigned int xOffset, unsigned int yOffset, Sprite &sprite, unsigned int width, unsigned int height) {
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	this->sprite = sprite;
	this->width = width;
	this->height = height;
}

//getters
unsigned int SpriteTile::getWidth() {
	return width;
}
unsigned int SpriteTile::getHeight() {
	return height;
}

//getters RGB
int SpriteTile::getPixelR(const int &x, const int &y) {
	if (x < 0 || x >= width || y < 0 || y >= height) return 0;
	int xa = x + xOffset;
	int ya = y + yOffset;
	return sprite.getPixelR(xa, ya);
}
int SpriteTile::getPixelG(const int &x, const int &y) {
	if (x < 0 || x >= width || y < 0 || y >= height) return 0;
	int xa = x + xOffset;
	int ya = y + yOffset;
	return sprite.getPixelR(xa, ya);
}
int SpriteTile::getPixelB(const int &x, const int &y) {
	if (x < 0 || x >= width || y < 0 || y >= height) return 0;
	int xa = x + xOffset;
	int ya = y + yOffset;
	return sprite.getPixelR(xa, ya);
}