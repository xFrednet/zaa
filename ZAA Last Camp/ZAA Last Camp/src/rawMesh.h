#pragma once

#include <glew.h>
#include <freeglut.h>

class RawMesh {
private:
	GLuint vaoID = 0;
	unsigned int vertexCount = 0;

public:
	RawMesh();
	RawMesh(GLuint &vaoID, int vertexCount);

	GLuint getVAOID();
	int getVertexCount();

};