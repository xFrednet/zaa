#pragma once
#include <mat4x4.hpp>
#include <vec3.hpp>

namespace maths {
	glm::mat4x4 createTransformationMatrix(const glm::vec3 &transformation, const float &rx, const float &ry, const float &rz, const float &scale);
	glm::mat4x4 createViewMatrix(const glm::vec3 &position, const float &yaw, const float &pitch);
};