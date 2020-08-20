#pragma once
#include <freeglut.h>
#include <iostream>
#include <mat4x4.hpp>
#include <string>

const int DEBUG = 3;

namespace console {
	void log(std::string log, int type);
	void log(std::string log, std::string log2, int type);
	void log(std::string log, int log2, std::string log3, int type);
	void log(std::string log, int log2, std::string log3, int log4, int type);
	void log(std::string log, GLuint log2, int type);
	void log(std::string log, int log2, int type);
	void err(std::string log);
	void err(std::string log, DWORD log2);
	void err(std::string log, std::string log2);
	void err(std::string log, std::string log2, std::string log3);
	void err(std::string log, std::string log2, std::string log3, std::string log4);
}