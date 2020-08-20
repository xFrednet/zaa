#include <glew.h>
#include <freeglut.h>
#include <mat4x4.hpp>

#include "debug.h"
#include "maths.h"
#include "model.h"
#include "rawModel.h"
#include "staticShader.h"
#include "texturedModel.h"
#include "mainRenderer.h"

const float PI = 3.1415926535f;

MainRenderer::MainRenderer() {}
MainRenderer::MainRenderer(StaticShader &shader) {
	projectionMatrix = createProjectionMatrix();
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}

glm::mat4x4 MainRenderer::createProjectionMatrix() {
	glm::mat4 matrix(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	float aspectRatio = (float)DisplayManager::width / (float)DisplayManager::height;
	float yScale = (float)((1.0f / std::tan(FOV / 2 / 180 * PI)) * aspectRatio);
	float xScale = yScale / aspectRatio;
	float frustumLength = FAR_PLANE - NEAR_PLANE;

	matrix[0][0] = xScale;
	matrix[1][1] = yScale;
	matrix[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustumLength);
	matrix[2][3] = -1;
	matrix[3][2] = -((2 * NEAR_PLANE * FAR_PLANE) / frustumLength);
	matrix[3][3] = 0;

	return matrix;
}

void MainRenderer::prepare() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
}

void MainRenderer::bindVertexAttribs(const int attribCount) {
	for (int i = 0; i < attribCount; i++) {
		glEnableVertexAttribArray(i);
	}
}

void MainRenderer::unbindVertexAttribs(const int attribCount) {
	for (int i = 0; i < attribCount; i++) {
		glDisableVertexAttribArray(i);
	}
}