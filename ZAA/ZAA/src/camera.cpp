#include <mat4x4.hpp>
#include <vec3.hpp>

#include "camera.h"

Camera::Camera() : Entity() {}
Camera::Camera(glm::vec3 &position) : Entity(position) {
	pitch = 0;
	yaw = 0;
	roll = 0;
}

glm::mat4x4 Camera::getViewMatrix() {
	return maths::createViewMatrix(position, yaw, pitch);
}
