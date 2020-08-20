#pragma once
#include <glew.h>
#include <freeglut.h>
#include <string>
#include <vector>

#include "rawMesh.h"
#include "sprite.h"
#include "texture.h"
#include "texturedMesh.h"

static const std::string resPath = "E:\\Libraries\\Visual Studio Projects\\ZAA Last Camp\\ZAA Last Camp\\res\\";

class Loader {
private:
	std::vector<GLuint> VAOs;
	std::vector<GLuint> VBOs;
	std::vector<GLuint> textures;

	//models
	void bindVBO(int index, std::vector<float> &data, int dataSize);

public:
	//constructor
	Loader();

	//models
	RawMesh loadToVAO(std::vector<float> positions, std::vector<float> texCoords, std::vector<float> normals, std::vector<int> indexBuffer);
	
	//obj Loader
	TexturedMesh loadMesh(const char *filePath, const char *imagePath, const bool defaultPath = true);

	//textures
	Texture loadTexture(const char *filePath, const bool defaultPath = true);

	//util
	void cleanUp();
};

namespace loader {
	std::string readFile(const char *filePath, const bool defaultPath = true);
	
	//textures
	Sprite loadSprite(const char *filePath, const bool defaultPath = true);
}