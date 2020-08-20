#include "renderer.h"

#include <glew.h>
#include <freeglut.h>
#include <mat4x4.hpp>
#include <vec4.hpp>

#include "displayManager.h"
#include "shader.h"

const float PI = 3.1415926535f;

//constructor
Renderer::Renderer() {}
Renderer::Renderer(Shader &shader) {
	const float fov = 70.0f;
	const float nearPlane = 0.1f;
	const float farPlane = 1000.0f;
	shader.start();
	shader.loadProjectionMatrix(createProjectionMatrix(fov, nearPlane, farPlane));
	shader.stop();
}

//util
void Renderer::bindVertexAttribs(int count) {
	for (int i = 0; i < count; i++) {
		glEnableVertexAttribArray(i);
	}
}
void Renderer::unbindVertexAttribs(int count) {
	for (int i = 0; i < count; i++) {
		glDisableVertexAttribArray(i);
	}
}
glm::mat4x4 Renderer::createProjectionMatrix(const float &fov, const float &nearPlane, const float &farPlane) {
	glm::mat4x4 matrix(
		glm::vec4(1, 0, 0, 0),
		glm::vec4(0, 1, 0, 0),
		glm::vec4(0, 0, 1, 0),
		glm::vec4(0, 0, 0, 1));
	float aspectRation = (float)displaymanager::getWidth() / (float)displaymanager::getHeight();
	float yScale = (float)((1.0f / std::tan(fov / 2 / 180 * PI)) * aspectRation);
	float xScale = yScale / aspectRation;
	float frustumLength = farPlane - nearPlane;

	matrix[0][0] = xScale;
	matrix[1][1] = yScale;
	matrix[2][2] = -((farPlane + nearPlane) / frustumLength);
	matrix[2][3] = -1;
	matrix[3][2] = -((2 * nearPlane * farPlane) / frustumLength);
	matrix[3][3] = 0;

	return matrix;
}

//other
void Renderer::prepare() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
}
