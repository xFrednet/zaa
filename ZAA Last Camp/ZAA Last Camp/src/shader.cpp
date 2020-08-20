#include "shader.h"

#include <glew.h>
#include <freeglut.h>
#include <mat4x4.hpp>
#include <iostream>
#include <string>

#include "console.h"
#include "loader.h"
#include "light.h"

//constructor
Shader::Shader() {}
Shader::Shader(const char *vertexShader, const char *fragmentShader) {
	//loading shaders
	vertexShaderID = loadShader(vertexShader, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentShader, GL_FRAGMENT_SHADER);
	
	//creating program
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID); 
	setupDefaultAttributes();
	setupAttributes();
	glLinkProgram(programID);
	glValidateProgram(programID);
	setupDefaultUniformLocations();
	setupUniformLocations();
}

//util
GLuint Shader::loadShader(const char *shaderpath, GLuint shaderType) {
	GLuint shaderID = glCreateShader(shaderType);
	int result = GL_FALSE;
	std::string shaderSrcString = loader::readFile(shaderpath);
	const char *shaderSrc = shaderSrcString.c_str();

	// Compile shader
	glShaderSource(shaderID, 1, &shaderSrc, NULL);
	glCompileShader(shaderID);

	//error check
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int logLength = 0;
		GLchar errorLog;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		glGetShaderInfoLog(shaderID, logLength, NULL, &errorLog);
		console::err("Shader: compile Error: ", errorLog);
	}
	else {
		console::log("Shader: Created Shader successful (Type ", shaderType, ")", 3);
	}

	return shaderID;
}
GLuint Shader::getUniformLocation(const char *uniformName) {
	return glGetUniformLocation(programID, uniformName);
}
void Shader::bindAttribute(const GLuint location, const char *name) {
	glBindAttribLocation(programID, location, name);
}

//uniform value Loader
void Shader::loadMatrix(const GLuint &location, glm::mat4x4 &matrix) {
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}
void Shader::loadVec3(const GLuint &location, glm::vec3 &vec3) {
	glUniform3fv(location, 1, &vec3[0]);
}

//uniform loader
void Shader::loadProjectionMatrix(glm::mat4x4 &projectionMatrix) {
	//error check
	if (projectionMatrixLoaction == -1) {
		
		//prints the Error message
		console::err("Shader: unabel to load the ProjectionMatrix (projectionMatrixLoaction = -1)");
		
		//returns without loading the Matrix
		return;
	}

	//loads the Matrix
	loadMatrix(projectionMatrixLoaction, projectionMatrix);
}
void Shader::loadTransformationMatrix(glm::mat4x4 &transformationMatrix) {
	//error check
	if (transformationMatrixLoaction == -1) {
		
		//prints the Error message
		console::err("Shader: unabel to load the TransformationMatrix (transformationMatrixLoaction = -1)");
		
		//returns without loading the Matrix
		return;
	}

	//loads the Matrix
	loadMatrix(transformationMatrixLoaction, transformationMatrix);
}
void Shader::loadViewMatrix(glm::mat4x4 &viewMatrix) {
	//error check
	if (transformationMatrixLoaction == -1) {
		
		//prints the Error message
		console::err("Shader: unabel to load the ViewMatrix (viewMatrixLocation = -1)");
		
		//returns without loading the Matrix
		return;
	}

	//loads the Matrix
	loadMatrix(viewMatrixLocation, viewMatrix);
}
void Shader::loadLight(Light &light) {
	loadVec3(lightPositionLocation, light.getPosition());
	loadVec3(lightColorLocation, light.getColor());
}

//start stop 
void Shader::start() {
	glUseProgram(programID);
}
void Shader::stop() {
	glUseProgram(0);
}

//virtual methods
void Shader::setupAttributes() {}
void Shader::setupUniformLocations(){}

//default config helper
void Shader::setupDefaultAttributes() {
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normals");
}
void Shader::setupDefaultUniformLocations() {
	projectionMatrixLoaction = getUniformLocation("projectionMatrix");
	transformationMatrixLoaction = getUniformLocation("transformationMatrix");
	viewMatrixLocation = getUniformLocation("viewMatrix");

	//light
	lightPositionLocation = getUniformLocation("lightPosition");
	lightColorLocation = getUniformLocation("lightColor");
}

//other
void Shader::cleanUp() {
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteProgram(programID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}