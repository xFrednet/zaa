#pragma once
#include <mat4x4.hpp>
#include <vec3.hpp>

namespace matrixmath {
	glm::mat4x4 getTransformationMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const float &scale);
	glm::mat4x4 getViewMatrix(const glm::vec3 &position, const float &yaw, const float &pitch);
}