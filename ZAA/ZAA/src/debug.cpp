#include <freeglut.h>
#include <iostream>
#include <mat4x4.hpp>
#include <string>
#include <vec4.hpp>

#include "debug.h"

void console::log(std::string log, int type) {
	if (type <= DEBUG) {
		std::cout << ">" << log << std::endl;
	}
}
void console::log(std::string log, std::string log2, int type) {
	if (type <= DEBUG) {
		std::cout << ">" << log << log2 << std::endl;
	}
}
void console::log(std::string log, int log2, std::string log3, int log4, int type) {
	if (type <= DEBUG) {
		std::cout << ">" << log << log2 << log3 << log4 << std::endl;
	}
}
void console::log(std::string log, int log2, std::string log3, int type) {
	if (type <= DEBUG) {
		std::cout << ">" << log << log2 << log3 << std::endl;
	}
}
void console::log(std::string log, GLuint log2, int type) {
	if (type <= DEBUG) {
		std::cout << ">" << log << log2 << std::endl;
	}
}
void console::log(std::string log, int log2, int type) {
	if (type <= DEBUG) {
		std::cout << ">" << log << log2 << std::endl;
	}
}

void console::err(std::string log) {
	std::cout << ">>Error: " << log << std::endl;
}
void console::err(std::string log, DWORD log2) {
	std::cout << ">>Error: " << log << log2 << std::endl;
}
void console::err(std::string log, std::string log2) {
	std::cout << ">>Error: " << log << log2 << std::endl;
}
void console::err(std::string log, std::string log2, std::string log3) {
	std::cout << ">>Error: " << log << log2 << log3 << std::endl;
}
void console::err(std::string log, std::string log2, std::string log3, std::string log4) {
	std::cout << ">>Error: " << log << log2 << log3 << log4 << std::endl;
}