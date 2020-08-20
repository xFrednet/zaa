#pragma once
#include <freeglut.h>
#include <vec3.hpp>
#include <mat4x4.hpp>

#include "rawModel.h"
#include "sprite.h"

class Terrain {
private:
	float MAX_TERRAIN_HEIGHT = 2;
	float TERRAIN_WIDTH_HEIGHT = 10;
	glm::vec3 position;

	float getHeight(Sprite &sprite, const int &x, const int &y);

public:
	RawModel rawModel;
	GLuint textureID;

	Terrain();
	Terrain(const char *fileName, int x, int y, Loader loader);

	glm::mat4x4 getTransformationMatrix();

};
