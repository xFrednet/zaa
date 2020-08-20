#pragma once
#include <vec3.hpp>
#include <mat4x4.hpp>

#include "entity.h"
#include "maths.h"

class Camera : public Entity {
public:

	float pitch, yaw, roll;

	Camera();
	Camera(glm::vec3 &position);
	glm::mat4x4 getViewMatrix();
};