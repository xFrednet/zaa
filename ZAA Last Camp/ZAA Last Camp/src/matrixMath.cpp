#include "matrixMath.h"

#include <gtc\matrix_transform.hpp>
#include <mat4x4.hpp>
#include <vec3.hpp>

const float PI = 3.14159265358979323846f;

glm::mat4x4 matrixmath::getTransformationMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const float &scale) {
	glm::mat4x4 matrix(
		glm::vec4(1, 0, 0, 0),
		glm::vec4(0, 1, 0, 0),
		glm::vec4(0, 0, 1, 0),
		glm::vec4(0, 0, 0, 1));
	matrix = glm::translate(matrix, position);
	matrix = glm::rotate(matrix, (float)(rotation.x / 180.0 * PI), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, (float)(rotation.y / 180.0 * PI), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, (float)(rotation.z / 180.0 * PI), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
	return matrix;
}

glm::mat4x4 matrixmath::getViewMatrix(const glm::vec3 &position, const float &yaw, const float &pitch) {
	glm::mat4x4 matrix(
		glm::vec4(1, 0, 0, 0),
		glm::vec4(0, 1, 0, 0),
		glm::vec4(0, 0, 1, 0),
		glm::vec4(0, 0, 0, 1));
	matrix = glm::rotate(matrix, (float)(pitch / 180 * PI), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, (float)(yaw / 180 * PI), glm::vec3(0, 1, 0));
	matrix = glm::translate(matrix, glm::vec3(-position.x, -position.y, -position.z));
	return matrix;
}