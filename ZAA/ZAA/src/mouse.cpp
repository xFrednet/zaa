#include <iostream>
#include "displayManager.h"
#include "mouse.h"

void mouseFunk(int button, int pressed, int x, int y) {
	mouse::buttons[button] = !pressed;
}

bool mouse::isPressed(int button) {
	return buttons[button];
}

float mouse::getGLx() {
	return GLx;
}
float mouse::getGLy() {
	return GLy;
}

void mouseMotion(int x, int y) {
	if (!mouse::buttons[0]) return;
	mouse::x = x;
	mouse::y = y;
	mouse::GLx = (float)((float)x / (float)DisplayManager::getWidth() * 2 - 1) * -1;
	mouse::GLy = (float)((float)y / (float)DisplayManager::getHeight() * 2 - 1) * -1;
}