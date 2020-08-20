#pragma once
#include <vec3.hpp>

#include "camera.h"
#include "keyboard.h"

class ControlableCamera : public Camera {
private:
	const float speed = 0.01f;
public:
	ControlableCamera();
	ControlableCamera(glm::vec3 &position);
	void update() override;
};
