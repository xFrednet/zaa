#include "mouse.h"

#include <glew.h>
#include <freeglut.h>

#include "displayManager.h"

void mouseMotion(int x, int y) {
	mouse::x = x;
	mouse::y = y;
	mouse::glX = ((float)x / (float)displaymanager::getWidth()) * 2;
	mouse::glY = ((float)y / (float)displaymanager::getHeight()) * 2;
}
void mouseAction(int button, int state, int x, int y) {
	if (button >= mouse::buttonCount || button < 0) return;
	if (state == 1) {
		mouse::buttons[button] = true;
	}
	else {
		mouse::buttons[button] = false;
	}
}

//mouse namespace

void mouse::update() {
	if (!isButtonDown(GLUT_LEFT_BUTTON)) {
		motionLastUpdateX = x - lastUpdateX;
		motionLastUpdateY = y - lastUpdateY;
	}
	else {
		motionLastUpdateX = 0;
		motionLastUpdateY = 0;
	}
	lastUpdateX = x;
	lastUpdateY = y;
}

//getters
bool mouse::isButtonDown(int button) {
	return buttons[button];
}
float mouse::getGlX() {
	return glX;
}
float mouse::getGlY() {
	return glY;
}
int mouse::getButtonCount() {
	return buttonCount;
}
int mouse::getXMotionLastUpdate() {
	return motionLastUpdateX;
}
int mouse::getYMotionLastUpdate() {
	return motionLastUpdateY;
}