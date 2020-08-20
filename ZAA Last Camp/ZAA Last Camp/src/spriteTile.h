#pragma once
#include "sprite.h"

#include <vector>

class SpriteTile {
protected:
	unsigned int xOffset = 0;
	unsigned int yOffset = 0;

	unsigned int width = 0;
	unsigned int height = 0;

	Sprite sprite;
public:
	//constructor
	SpriteTile();
	SpriteTile(unsigned int xOffset, unsigned int yOffset, Sprite &sprite, unsigned int width, unsigned int height);

	//getters
	unsigned int getWidth();
	unsigned int getHeight();

	//getters RGB
	int getPixelR(const int &x, const int &y);
	int getPixelG(const int &x, const int &y);
	int getPixelB(const int &x, const int &y);
};
