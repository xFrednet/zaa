#pragma once
#include <mat4x4.hpp>
#include <vec3.hpp>

#include "maths.h"
#include "texturedModel.h"

class Model {
public:
	TexturedModel texturedModel;
	glm::vec3 position;
	float rotX, rotY, rotZ;
	float scale;
	Model(TexturedModel &texturedModel, glm::vec3 &position, float rotX, float rotY, float rotZ, float scale);
	Model(TexturedModel &texturedModel, glm::vec3 &position, float scale);
	Model();

	void increasePosition(float dx, float dy, float dz);
	void increaseRotation(float dx, float dy, float dz);
	glm::mat4x4 getTransformationMatrix();
};
