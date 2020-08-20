#pragma once
#include "shader.h"

#include <glew.h>
#include <freeglut.h>

#define STATICSHADER_VERTEX_SHADER_PATH "shader\\staticVertex.Shader"
#define STATICSHADER_FRAGMENT_SHADER_PATH "shader\\staticFragment.Shader"

class StaticShader : public Shader {
private:
protected:
public:

	//constructor
	StaticShader();
	StaticShader(bool generate);

};