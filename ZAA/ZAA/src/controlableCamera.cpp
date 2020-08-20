#include <freeglut.h>
#include <math.h>
#include <vec3.hpp>

#include "controlableCamera.h"
#include "debug.h"
#include "keyboard.h"
#include "mouse.h"

ControlableCamera::ControlableCamera() {}
ControlableCamera::ControlableCamera(glm::vec3 &position) : Camera(position) {}

void ControlableCamera::update() {
	
	pitch = mouse::getGLy() * -90;
	yaw = mouse::getGLx() * 180;

	glm::vec3 v;

	//up down
	if (isKeyDown('x')) v.y -= speed / 2;
	if (isKeyDown('y')) v.y += speed / 2;
	
	//motion
	if (isKeyDown('w')) v.z -= speed;
	if (isKeyDown('s')) v.z += speed;
	if (isKeyDown('a')) v.x -= speed;
	if (isKeyDown('d')) v.x += speed;

	//debug speedUp
	if (DEBUG >= 1) {
		if (isKeyDown('e')) {
			if (isKeyDown('w')) v.z -= speed * 4 * 2;
			if (isKeyDown('s')) v.z += speed * 4 * 2;
			if (isKeyDown('a')) v.x -= speed * 2 * 2;
			if (isKeyDown('d')) v.x += speed * 2 * 2;
			if (isKeyDown('x')) v.y -= speed;
			if (isKeyDown('y')) v.y += speed;
		}
	}

	float angle = (3.141592653589f / 180) * yaw;

	//forward backwords
	position.x += v.z * sin(-angle);
	position.z += v.z * cos(-angle);
	
	//Left Right
	position.x += v.x * cos(angle);
	position.z += v.x * sin(angle);

	//up down
	position.y += v.y;

}