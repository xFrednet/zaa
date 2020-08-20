#include "terrain.h"

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



//constructor
Terrain::Terrain() {}
Terrain::Terrain(const char *depthMapPath, Loader &loaderClass, TerrainShader &terrainShader, TerrainRenderer &terrainRenderer) {
	this->depthMapPath = depthMapPath;
	this->loaderClass = loaderClass;
	this->terrainShader = terrainShader;
	this->terrainRenderer = terrainRenderer;
	loadTerrainTiles(depthMapPath);
}


//getters
void Terrain::getHeight(const float &x, const float &y) {

}

//util
void Terrain::loadTerrainTiles(const char *depthMapPath) {
	//terrainTile
	depthMap = loader::loadSprite(depthMapPath);
	TerrainTile tile;
	SpriteTile spriteTile;
	for (unsigned int y = 0; y < depthMap.getHeight() / pixelsPerTerrainTile; y++) {
		for (unsigned int x = 0; x < depthMap.getWidth() / pixelsPerTerrainTile; x++) {
			spriteTile = SpriteTile(x * pixelsPerTerrainTile, y * pixelsPerTerrainTile, depthMap, pixelsPerTerrainTile, pixelsPerTerrainTile);
			tile = TerrainTile(glm::vec2(x, y), spriteTile, loaderClass);
			tiles.push_back(tile);
		}
	}
}
void Terrain::render(Camera &camera) {
	terrainShader.start();
	terrainShader.loadViewMatrix(camera.getViewMatrix());
	terrainRenderer.render(tiles, terrainShader);
	terrainShader.stop();
}