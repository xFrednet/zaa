#include <glew.h>
#include <freeglut.h>
#include <mat4x4.hpp>

#include "debug.h"
#include "shader.h"
#include "staticShader.h"

void StaticShader::loadTransformationMatrix(glm::mat4x4 &matrix) {
	loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4x4 &matrix) {
	loadMatrix(location_projectionMatrix, matrix);
}

void StaticShader::loadViewMatrix(glm::mat4x4 &matrix) {
	loadMatrix(location_viewMatrix, matrix);
}

void StaticShader::bindAttributes() {
	bindAttribute(0, "positions");
	bindAttribute(1, "textureCoords");
}

void StaticShader::getUniformLocations() {
	location_transformationMatrix = getUniformLocation("transformationMatrix");
	location_projectionMatrix = getUniformLocation("projectionMatrix");
	location_viewMatrix = getUniformLocation("viewMatrix");
}

StaticShader::StaticShader(bool hi) : Shader() {
	Shader::loadProgram(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
}
StaticShader::StaticShader() : Shader() {}
