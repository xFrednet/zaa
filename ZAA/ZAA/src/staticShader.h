#pragma once
#include <freeglut.h>
#include <mat4x4.hpp>
#include <string>

#include "shader.h"

class StaticShader : public Shader {
private:
	const char *VERTEX_SHADER_PATH = "vertexShader.txt";
	const char *FRAGMENT_SHADER_PATH = "fragmentShader.txt"; 

	GLuint location_transformationMatrix;
	GLuint location_projectionMatrix;
	GLuint location_viewMatrix;
	void getUniformLocations() override;
	void bindAttributes() override;
public:
	StaticShader();
	StaticShader(bool hi);
	void loadTransformationMatrix(glm::mat4x4 &matrix);
	void loadProjectionMatrix(glm::mat4x4 &matrix);
	void loadViewMatrix(glm::mat4x4 &matrix);
};
