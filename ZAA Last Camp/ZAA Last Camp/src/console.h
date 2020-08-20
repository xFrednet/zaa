#pragma once
#include <glew.h>
#include <freeglut.h>
#include <string>

#define DEBUG 1

namespace console {
	//log
	void log(std::string arg0, int level);
	void log(std::string arg0, std::string arg1, int level);
	void log(std::string arg0, std::string arg1, std::string arg2, int level);
	void log(std::string arg0, std::string arg1, std::string arg2, std::string arg3, int level);
	void log(std::string arg0, GLuint arg1, std::string arg2, int level);

	//err
	void err(std::string arg0);
	void err(std::string arg0, std::string arg1); 
	void err(std::string arg0, std::string arg1, std::string arg2);
	void err(std::string arg0, std::string arg1, std::string arg2, std::string arg3);
	void err(std::string arg0, DWORD arg1);

	//util
	void logVersions();
}
