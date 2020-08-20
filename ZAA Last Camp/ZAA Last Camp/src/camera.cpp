#include "camera.h"
#include "entity.h"

#include <mat4x4.hpp>
#include <vec3.hpp>

#include "matrixMath.h"

//constructor
Camera::Camera() : Entity() {}
Camera::Camera(glm::vec3 position) : Entity(position) {}

//getters
glm::mat4x4 Camera::getViewMatrix() {
	return matrixmath::getViewMatrix(position, yaw, pitch);
}