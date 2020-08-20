#include <freeglut.h>

#include "rawModel.h"

RawModel::RawModel() {}
RawModel::RawModel(const GLuint &vaoID, const int &vertexCount) {
	this->vaoID = vaoID;
	this->vertexCount = vertexCount;
}

int RawModel::getVertexCount() {
	return vertexCount;
}
GLuint RawModel::getVaoID() {
	return vaoID;
}