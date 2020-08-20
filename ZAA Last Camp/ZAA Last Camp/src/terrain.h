#pragma once
#include <glew.h>
#include <freeglut.h>
#include <vector>
#include <vec2.hpp>

#include "terrainRenderer.h"
#include "terrainShader.h"
#include "sprite.h"
#include "spriteTile.h"
#include "terrainTile.h"
#include "loader.h"
#include "camera.h"

class Terrain {
private:
protected:
	//terrainTiles
	std::vector<TerrainTile> tiles;
	unsigned int pixelsPerTerrainTile = 100;

	//shader & renderer
	TerrainShader terrainShader;
	TerrainRenderer terrainRenderer;

	//depthMap
	const char *depthMapPath;
	Sprite depthMap;

	//util
	Loader loaderClass;
	void loadTerrainTiles(const char *depthMapPath);

public:
	//constructor
	Terrain();
	Terrain(const char *depthMapPath, Loader &loaderClass, TerrainShader &terrainShader, TerrainRenderer &terrainRenderer);

	//util
	void render(Camera &camera);

	//getters
	void getHeight(const float &x, const float &y);
};