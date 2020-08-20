#pragma once
#include <freeglut.h>
#include <string>
#include <vector>

#include "rawModel.h"
#include "sprite.h"
#include "texturedModel.h"

class Loader {
private:
	std::vector<GLuint> VAOs;
	std::vector<GLuint> VBOs;
	std::vector<GLuint> textureIDs;
	
	//VAO
	GLuint createVAO();
	void unbindVAO();
	//VBO
	void storeDataInAttributeList(int attributeNumber, int coordinateSize, const float data[], const int VertexIndexes);
	void bindIndicesBuffer(const int indices[], const int vertexCount);

public:
	//Models
	RawModel loadToVAO(const float positions[], const float texturePositions[], const float normals[], const int VertexIndexes, const int indices[], const int vertexCount);
	TexturedModel loadModel(const char *fileName);
	
	//Textures
	GLuint loadTexture(const char *filename);
	Sprite loadImage(const char *fileName);
	
	//Other
	std::string readFile(std::string filePath);
	void cleanUp();

};