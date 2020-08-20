#include <glew.h>
#include <algorithm>
#include <freeglut.h>
#include <fstream>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <mat4x4.hpp>
#include <string>
#include <vec4.hpp>
#include <vector>

#include "debug.h"
#include "loader.h"
#include "shader.h"

void Shader::cleanUp() {
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteProgram(programID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	console::log("Shader: deleted ShaderProgram", 2);
}

void Shader::start() {
	glUseProgram(programID);
}

void Shader::stop() {
	glUseProgram(0);
}

GLuint Shader::getUniformLocation(const char *name) {
	GLuint location = glGetUniformLocation(programID, name);
	return location;
}

void Shader::bindAttribute(const GLuint &attribute, const char *name) {
	glBindAttribLocation(programID, attribute, name);
}

GLuint Shader::loadShader(const char *filePath, GLuint type) {
	GLuint shaderID = glCreateShader(type);
	int result = GL_FALSE;
	Loader loader;
	std::string shaderStr = loader.readFile(filePath);
	const char *shaderSrc = shaderStr.c_str();
	
	// Compile shader
	console::log("Shader: Compiling Shader. type: ", type, 2);
	glShaderSource(shaderID, 1, &shaderSrc, NULL);
	glCompileShader(shaderID);

	// Check shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int logLength;
		GLchar error;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		glGetShaderInfoLog(shaderID, logLength, NULL, &error);
		console::err(&error);
	}
	else {
		console::log("Shader: Created Shader successful", 3);
	}

	return shaderID;
}

void Shader::loadMatrix(const GLuint &location, glm::mat4x4 &matrix) {
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::bindAttributes() {
	console::err("Shader: Linking Error (bindAttributes())");
}

void Shader::getUniformLocations() {
	console::err("Shader: Linking Error (getUniformLocations())");
}
void Shader::loadProgram(const char *vertexShader, const char *fragmentShader) {
	//loadShaders
	vertexShaderID = loadShader(vertexShader, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentShader, GL_FRAGMENT_SHADER);

	//createProgram
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	bindAttributes();
	glLinkProgram(programID);
	glValidateProgram(programID);
	getUniformLocations();

	console::log("StaticShader: Created StaticShaderProgram successful", 1);
}