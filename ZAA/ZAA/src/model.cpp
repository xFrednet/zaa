#include <mat4x4.hpp>
#include <vec3.hpp>

#include "debug.h"
#include "maths.h"
#include "model.h"
#include "texturedModel.h"

Model::Model() {}

Model::Model(TexturedModel &texturedModel, glm::vec3 &position, float rotX, float rotY, float rotZ, float scale) {
	this->texturedModel = texturedModel;
	this->position = position;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
}

Model::Model(TexturedModel &texturedModel, glm::vec3 &position, float scale) {
	this->texturedModel = texturedModel;
	this->position = position;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 0;
	this->scale = scale;
}

void Model::increasePosition(float dx, float dy, float dz) {
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

void Model::increaseRotation(float dx, float dy, float dz) {
	rotX += dx;
	rotY += dy;
	rotZ += dz;
}

glm::mat4x4 Model::getTransformationMatrix() {
	return maths::createTransformationMatrix(position, rotX, rotY, rotZ, scale);
}