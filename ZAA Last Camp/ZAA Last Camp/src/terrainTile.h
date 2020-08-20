#pragma once
#include <glew.h>
#include <freeglut.h>
#include <vec3.hpp>
#include <vec2.hpp>
#include <mat4x4.hpp>

#include "rawMesh.h"
#include "texturedMesh.h"
#include "texture.h"
#include "loader.h"
#include "matrixMath.h"
#include "spriteTile.h"

#define WORLDTILE_WIDTH_HEIGHT 16
#define WORLDTILE_MAX_HEIGHT 4

class TerrainTile {
private:
	//util
	float getHeight(SpriteTile &depthMap, const unsigned int &x, const unsigned int &y);
protected:
	glm::vec2 position;
	TexturedMesh texturedMesh;
	
	//util
	TexturedMesh loadTerrainTile(SpriteTile depthMap, Loader &loaderc);

public:
	//constructor
	TerrainTile();
	TerrainTile(glm::vec2 position, SpriteTile depthMap, Loader &loaderc);

	//getters
	glm::mat4x4 getTransformationMatrix();
	TexturedMesh getTexturedMesh();
	
};