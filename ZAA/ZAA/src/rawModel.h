#pragma once
#include <freeglut.h>

class RawModel {
private:
	GLuint vaoID = 0;
	int vertexCount = 0;

public:

	RawModel();
	RawModel(const GLuint &vaoID, const int &vertexCount);

	int getVertexCount();
	GLuint getVaoID();

};
