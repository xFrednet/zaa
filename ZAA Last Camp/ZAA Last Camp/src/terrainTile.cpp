#include "terrainTile.h"

#include <glew.h>
#include <freeglut.h>
#include <vec3.hpp>
#include <mat4x4.hpp>

#include "rawMesh.h"
#include "texturedMesh.h"
#include "texture.h"
#include "loader.h"
#include "matrixMath.h"
#include "sprite.h"
#include "spriteTile.h"

//constructors
TerrainTile::TerrainTile() {}
TerrainTile::TerrainTile(glm::vec2 position, SpriteTile depthMap, Loader &loaderc) {
	this->position = glm::vec2(position.x * WORLDTILE_WIDTH_HEIGHT, position.y * WORLDTILE_WIDTH_HEIGHT);
	texturedMesh = loadTerrainTile(depthMap, loaderc);
}

//util
TexturedMesh TerrainTile::loadTerrainTile(SpriteTile depthMap, Loader &loaderc) {
	unsigned int depthMapWidthHeight = depthMap.getHeight();
	float positionSpace = WORLDTILE_WIDTH_HEIGHT / (float)(depthMapWidthHeight - 1);

	std::vector<float> positions;
	std::vector<float> textureCoords;
	std::vector<float> normals;

	//fill vectors
	for (unsigned int y = 0; y < depthMapWidthHeight; y++) {
		float yPos = positionSpace * y;
		for (unsigned int x = 0; x < depthMapWidthHeight; x++) {

			//positions
			positions.push_back(positionSpace * x);
			positions.push_back(getHeight(depthMap, x, y));
			positions.push_back(yPos);

			//textureCoords
			textureCoords.push_back((float)(x % 2));
			textureCoords.push_back((float)(y % 2));

			//normals
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);

		}
	}

	//index Buffer
	std::vector<int> indexBuffer;
	for (unsigned int y = 0; y < depthMapWidthHeight - 1; y++) {
		for (unsigned int x = 0; x < depthMapWidthHeight - 1; x++) {

			//  P1 # P4
			//  #######
			//  P2 # P3

			int p1 = x + y * depthMapWidthHeight;
			int p2 = x + (y + 1) * depthMapWidthHeight;
			int p3 = (x + 1) + (y + 1) * depthMapWidthHeight;
			int p4 = (x + 1) + y * depthMapWidthHeight;

			//  #
			//  ###
			//  #####
			indexBuffer.push_back(p1);
			indexBuffer.push_back(p2);
			indexBuffer.push_back(p3);

			//  #####
			//    ###
			//      #
			indexBuffer.push_back(p1);
			indexBuffer.push_back(p3);
			indexBuffer.push_back(p4);

		}
	}

	RawMesh rawMesh = loaderc.loadToVAO(positions, textureCoords, positions, indexBuffer);
	Texture texture = loaderc.loadTexture("texture\\test.png");
	TexturedMesh texturedMesh(rawMesh, texture);

	return texturedMesh;
}
float TerrainTile::getHeight(SpriteTile &depthMap, const unsigned int &x, const unsigned int &y) {
	float total = 0;
	total += depthMap.getPixelR(x, y);
	total += depthMap.getPixelG(x, y);
	total += depthMap.getPixelB(x, y);

	float heightPercent = (float)(total / (255 * 3)) * 2 - 1;
	return WORLDTILE_MAX_HEIGHT * heightPercent;
}

//getters
glm::mat4x4 TerrainTile::getTransformationMatrix() {
	return matrixmath::getTransformationMatrix(glm::vec3(position.x, 0, position.y), glm::vec3(0, 0, 0), 1);
}
TexturedMesh TerrainTile::getTexturedMesh() {
	return texturedMesh;
}