#pragma once
#include <glew.h>
#include <freeglut.h>
#include <mat4x4.hpp>
#include <vec3.hpp>

#include "light.h"

class Shader {
private:
	GLuint programID = 0;
	GLuint vertexShaderID = 0;
	GLuint fragmentShaderID = 0;

protected:
	//uniform matix locations
	GLuint projectionMatrixLoaction = 0;
	GLuint transformationMatrixLoaction = 0;
	GLuint viewMatrixLocation = 0;
	//uniform light location
	GLuint lightPositionLocation = 0;
	GLuint lightColorLocation = 0;

	//uniform value Loader
	void loadMatrix(const GLuint &location, glm::mat4x4 &matrix);
	void loadVec3(const GLuint &location, glm::vec3 &vec3);

	//util
	GLuint loadShader(const char *shaderpath, GLuint shaderType);
	GLuint getUniformLocation(const char *uniformName);
	void bindAttribute(const GLuint location, const char *name);

	//virtual methods 
	virtual void setupAttributes();
	virtual void setupUniformLocations();

	//default config helper
	void setupDefaultAttributes();
	void setupDefaultUniformLocations();

public:
	//constructor
	Shader();
	Shader(const char *vertexShader, const char *fragmentShader);

	//uniform loader
	void loadProjectionMatrix(glm::mat4x4 &projectionMatrix);
	void loadTransformationMatrix(glm::mat4x4 &transformationMatrix);
	void loadViewMatrix(glm::mat4x4 &viewMatrix);
	void loadLight(Light &light);

	//start stop
	void start();
	void stop();
	
	//other
	void cleanUp();
};