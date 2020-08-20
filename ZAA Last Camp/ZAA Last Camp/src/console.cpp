#include <glew.h>
#include <freeglut.h>
#include <glm.hpp>
#include <iostream>
#include <string>

#include "console.h"

std::string info = "[INFO] ";
std::string error = "[ERROR] ";

//log
void console::log(std::string arg0, int level) {
	if (level >= DEBUG) {
		std::cout << info << arg0 << std::endl;
	}
}
void console::log(std::string arg0, std::string arg1, int level) {
	if (level >= DEBUG) {
		std::cout << info << arg0 << arg1 << std::endl;
	}
}
void console::log(std::string arg0, std::string arg1, std::string arg2, int level) {
	if (level >= DEBUG) {
		std::cout << info << arg0 << arg1 << arg2 << std::endl;
	}
}
void console::log(std::string arg0, std::string arg1, std::string arg2, std::string arg3, int level) {
	if (level >= DEBUG) {
		std::cout << info << arg0 << arg1 << arg2 << arg3 << std::endl;
	}
}
void console::log(std::string arg0, GLuint arg1, std::string arg2, int level) {
	if (level >= DEBUG) {
		std::cout << info << arg0 << arg1 << arg2 << std::endl;
	}
}

//err
void console::err(std::string arg0) {
	std::cout << error << arg0 << std::endl;
}
void console::err(std::string arg0, std::string arg1) {
	std::cout << error << arg0 << arg1 << std::endl;
}
void console::err(std::string arg0, std::string arg1, std::string arg2) {
	std::cout << error << arg0 << arg1 << arg2 << std::endl;
}
void console::err(std::string arg0, std::string arg1, std::string arg2, std::string arg3) {
	std::cout << error << arg0 << arg1 << arg2 << arg3 << std::endl;
}
void console::err(std::string arg0, DWORD arg1) {
	std::cout << error << arg0 << arg1 << std::endl;
}
//util
void console::logVersions() {
	if (DEBUG > 0) {
		std::cout << info << "Debug Level:		" << DEBUG << std::endl;
		std::cout << info << "GLEW Version:		" << GLEW_VERSION << std::endl;
		std::cout << info << "FreeGLUT Version:	" << GLUT_VERSION << std::endl;
		std::cout << info << "GLM Version:		" << GLM_VERSION << std::endl;
		std::cout << info << "OpenGL Version:		" << GL_VERSION << std::endl;
		std::cout << info << std::endl;
	}
}