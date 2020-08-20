#pragma once
#include "camera.h"
#include "entity.h"

#include <vec3.hpp>

class ControllableCamera : public Camera {
private:
	float speed = 0.05f;
protected:
public:
	//constrctor
	ControllableCamera();
	ControllableCamera(glm::vec3 position);

	//update
	void update();
};