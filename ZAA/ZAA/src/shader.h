#pragma once

#include <freeglut.h>
#include <mat4x4.hpp>
#include <string>

class Shader {
protected: 
	
	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;
	
	GLuint getUniformLocation(const char *name);
	
	void loadProgram(const char *vertexShader, const char *fragmentShader);
	void bindAttribute(const GLuint &attribute, const char *name);
	void loadMatrix(const GLuint &location, glm::mat4x4 &matrix);

public:

	virtual void bindAttributes();
	virtual void getUniformLocations();
	GLuint loadShader(const char *filePath, GLuint type);
	void cleanUp();
	void start();
	void stop();
};
