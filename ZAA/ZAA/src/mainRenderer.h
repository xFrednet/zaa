#pragma once
#include <freeglut.h>
#include <glew.h>
#include <mat4x4.hpp>

#include "displayManager.h"
#include "model.h"
#include "staticShader.h"

class MainRenderer {
private:

	float FOV = 70.0f;
	float NEAR_PLANE = 0.1f;
	float FAR_PLANE = 1000.0f;

	glm::mat4x4 projectionMatrix;
	glm::mat4x4 createProjectionMatrix();

public:
	MainRenderer();
	MainRenderer(StaticShader &shader);
	void bindVertexAttribs(const int attribCount);
	void unbindVertexAttribs(const int attribCount);
	void prepare();
};
