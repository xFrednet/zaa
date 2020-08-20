#pragma once
#include <glew.h>
#include <freeglut.h>
#include <mat4x4.hpp>

#include "shader.h"

class Renderer {
private:
protected:
	//util
	void bindVertexAttribs(int count);
	void unbindVertexAttribs(int count);
	glm::mat4x4 createProjectionMatrix(const float &fov, const float &nearPlane, const float &farPlane);
public:
	//constructor
	Renderer();
	Renderer(Shader &shader);

	//other
	void prepare();
};