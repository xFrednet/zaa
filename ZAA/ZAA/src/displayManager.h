#pragma once
#include <string.h>

#include "keyboard.h"

namespace DisplayManager {
	static int width = 480;
	static int height = width / 16 * 9;

	static bool fullScreen = false;

	static char* title = "ZAA: Last Camp";

	void createWindow(int &argv, char** argc);
	void updateWindow();
	void setTitle(const char *title);
	void toggleFullScreen();

	int getWidth();
	int getHeight();
};
