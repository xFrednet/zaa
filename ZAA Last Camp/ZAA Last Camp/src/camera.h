#pragma once
#include "entity.h"

#include <mat4x4.hpp>
#include <vec3.hpp>

#include "matrixMath.h"

class Camera : public Entity {
protected:
	float yaw = 0;
	float pitch = 0;
public:
	//constructor 
	Camera();
	Camera(glm::vec3 position);

	//getters
	glm::mat4x4 getViewMatrix();
};