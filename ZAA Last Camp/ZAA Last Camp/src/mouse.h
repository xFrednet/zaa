#pragma once

#include <glew.h>
#include <freeglut.h>

void mouseMotion(int x, int y);
void mouseAction(int button, int state, int x, int y);

namespace mouse {

	const int buttonCount = 5;
	static bool buttons[buttonCount] = { 1 };
	static float glX = 0;
	static float glY = 0;
	static int x = 0;
	static int y = 0;
	static int lastUpdateX = 0;
	static int lastUpdateY = 0;
	static int motionLastUpdateX = 0;
	static int motionLastUpdateY = 0;
	
	void update();

	//getters
	bool isButtonDown(int button);
	float getGlX();
	float getGlY();
	int getButtonCount();
	int getXMotionLastUpdate();
	int getYMotionLastUpdate();

}