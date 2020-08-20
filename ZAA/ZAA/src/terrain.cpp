#include <iostream>
#include <freeglut.h>
#include <vector>
#include <vec3.hpp>
#include <mat4x4.hpp>

#include "loader.h"
#include "maths.h"
#include "rawModel.h"
#include "sprite.h"
#include "terrain.h"

Terrain::Terrain() {}
Terrain::Terrain(const char *fileName, int x, int y, Loader loader) {
	position.x = x * TERRAIN_WIDTH_HEIGHT;
	position.y = -(MAX_TERRAIN_HEIGHT / 2);
	position.z = y * TERRAIN_WIDTH_HEIGHT;
	Sprite sprite = loader.loadImage(fileName);

	std::vector<float> vertices;
	std::vector<float> textureCoords;
	std::vector<float> normals;
	std::vector<int> indices;

	float distance = TERRAIN_WIDTH_HEIGHT / sprite.width;

	for (int y = 0; y < sprite.height; y++) {
		for (int x = 0; x < sprite.width; x++) {
			//vertices
			vertices.push_back(x * distance);
			vertices.push_back(getHeight(sprite, x, y));
			vertices.push_back(y * distance);
			//textureCoords
			textureCoords.push_back(x % 2);
			textureCoords.push_back(y % 2);
			//normals
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);
		}
	}

	/* c0--c1 *
	*  c2--c3 */

	//GL_ELEMENT_ARRAY_BUFFER
	for (int y = 0; y < sprite.height - 1; y++) {
		for (int x = 0; x < sprite.width - 1; x++) {
			int c1 = (x + 1) + y * sprite.width;
			int c2 = x + (y + 1) * sprite.width;

			indices.push_back(x + y * sprite.width);	//c0
			indices.push_back(c2);
			indices.push_back(c1);

			indices.push_back(c2);
			indices.push_back((x + 1) + (y + 1) * sprite.width);	//c3
			indices.push_back(c1);
		}
	}

	rawModel = loader.loadToVAO(&vertices[0], &textureCoords[0], &normals[0], vertices.size() / 3, &indices[0], indices.size());
	textureID = loader.loadTexture("Sand.png");

}

float Terrain::getHeight(Sprite &sprite, const int &x, const int &y) {
	float total = 0;
	total += sprite.getPixelR(x, y);
	total += sprite.getPixelG(x, y);
	total += sprite.getPixelB(x, y);

	float totalP = (total / (255 * 3));
	totalP *= 3;
	totalP -= 1;
	float height = (totalP * MAX_TERRAIN_HEIGHT);
	return height;
}

glm::mat4x4 Terrain::getTransformationMatrix() {
	return maths::createTransformationMatrix(position, 0, 0, 0, 1);
}