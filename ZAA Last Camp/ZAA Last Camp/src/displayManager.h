#pragma once
#include <glew.h>
#include <freeglut.h>

#include "console.h"

namespace displaymanager {

	void createWindow(int &argv, char **argc);
	int getWidth();
	int getHeight();

	void update();
	void updateDisplay();
}