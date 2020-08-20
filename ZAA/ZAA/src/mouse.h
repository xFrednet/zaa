#pragma once

namespace mouse {
	const static int LEFT_BUTTON = 0;
	const static int RIGHT_BUTTON = 2;

	static bool buttons[20] = { false };
	static int x = -1;
	static int y = -1;
	static float GLx = -1;
	static float GLy = -1;
	
	bool isPressed(int button);
	float getGLx();
	float getGLy();
}

void mouseFunk(int button, int pressed, int x, int y);
void mouseMotion(int x, int y);