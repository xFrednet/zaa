#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <string.h>

#include "debug.h"
#include "displayManager.h"
#include "keyboard.h"
#include "mouse.h"

void displayFunktion() {}

void DisplayManager::updateWindow() {
	glutSwapBuffers();
}

void addFunctions() {
	
	//keyborad
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	
	//Mouse
	glutMouseFunc(mouseFunk);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mouseMotion);
	
	//display
	glutDisplayFunc(displayFunktion);

}

void addDepthTest() {
	glEnable(GL_DEPTH_TEST);
}

void DisplayManager::createWindow(int &argv, char **argc) {
	glutInit(&argv, argc);
	
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(title);

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	
	addFunctions();

	if (fullScreen == true) {
		glutFullScreen();
	}

	glewExperimental = TRUE;
	if (glewInit() != GLEW_OK) {
		console::err("glewInit failed, aborting.");
		system("Pause");
		exit(-1);
	}

	addDepthTest();

	console::log("DisplayManager: created Window", 3);

}

void DisplayManager::setTitle(const char *title) {
	glutSetWindowTitle(title);
}

void DisplayManager::toggleFullScreen() {
	glutFullScreenToggle();
	fullScreen = !fullScreen;
}

int DisplayManager::getWidth() {
	return glutGet(GLUT_WINDOW_WIDTH);
}
int DisplayManager::getHeight() {
	return glutGet(GLUT_WINDOW_HEIGHT);
}