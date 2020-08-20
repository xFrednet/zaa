#include <gtc\matrix_transform.hpp>
#include <iostream>
#include <mat4x4.hpp>
#include <vec3.hpp>

#include "debug.h"
#include "maths.h"

const double PI = 3.14159265358979323846;

glm::mat4x4 maths::createTransformationMatrix(const glm::vec3 &transformation, const float &rx, const float &ry, const float &rz, const float &scale) {
	glm::mat4 matrix(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	matrix = glm::translate(matrix, transformation);
	matrix = glm::rotate(matrix, (float) (rx / 180.0 * PI), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, (float) (ry / 180.0 * PI), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, (float) (rz / 180.0 * PI), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
	return matrix;
}

glm::mat4x4 maths::createViewMatrix(const glm::vec3 &position, const float &yaw, const float &pitch) {
	glm::mat4 matrix(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	matrix = glm::rotate(matrix, (float) (pitch / 180 * PI), glm::vec3(1, 0 , 0));
	matrix = glm::rotate(matrix, (float) (yaw / 180 * PI), glm::vec3(0, 1, 0));
	glm::vec3 negativePos(-position.x, -position.y, -position.z);
	matrix = glm::translate(matrix, negativePos);
	return matrix;
}

double toRadians(double angdeg) {
	return angdeg / 180 * PI;
}