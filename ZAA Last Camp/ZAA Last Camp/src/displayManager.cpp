#include "displayManager.h"

#include <glew.h>
#include <freeglut.h>

#include "console.h"
#include "keyboard.h"
#include "mouse.h"

int width = 500;
int height = width / 16 * 9;
char *title = "ZAA: Last Camp";

void displayFunktion() {
}

void addFunctions() {
	
	//keyboard
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);

	//mouse
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);

	//display
	glutDisplayFunc(displayFunktion);

}


//displaymanager methods
void displaymanager::createWindow(int &argv, char **argc) {
	glutInit(&argv, argc);

	//window
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(title);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	addFunctions();

	//GLEW
	glewExperimental = TRUE;
	if (glewInit() != GLEW_OK) {
		console::err("glewInit Failed!");
		system("pause");
		exit(-1);
	}

	//OpenGL method
	glEnable(GL_DEPTH_TEST);
	console::log("Created Window successfull", 1);
}

int displaymanager::getWidth() {
	return glutGet(GLUT_WINDOW_WIDTH);
}

int displaymanager::getHeight() {
	return glutGet(GLUT_WINDOW_HEIGHT);
}

void displaymanager::update() {
	glutMainLoopEvent();
}

void displaymanager::updateDisplay() {
	glutSwapBuffers();
	glutMainLoopEvent();
}