#pragma once
#include "renderer.h"

#include <glew.h>
#include <freeglut.h>
#include <vector>

#include "terrainShader.h"
#include "terrainTile.h"

class TerrainRenderer : public Renderer {
protected:
	//render
	void renderTerrainTile(TerrainTile &terrainTile, TerrainShader &terrainShader);
public:
	//constructor
	TerrainRenderer();
	TerrainRenderer(TerrainShader &terrainShader);

	//render
	void render(std::vector<TerrainTile> &terrainTiles, TerrainShader &terrainShader);

};