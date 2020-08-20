#include "rawMesh.h"

#include <glew.h>
#include <freeglut.h>

RawMesh::RawMesh() {}
RawMesh::RawMesh(GLuint &vaoID, int vertexCount) {
	this->vaoID = vaoID;
	this->vertexCount = vertexCount;
}

//getters
GLuint RawMesh::getVAOID() {
	return vaoID;
}
int RawMesh::getVertexCount() {
	return vertexCount;
}