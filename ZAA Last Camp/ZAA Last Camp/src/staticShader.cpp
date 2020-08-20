#include "staticShader.h"
#include "shader.h"

#include <glew.h>
#include <freeglut.h>
#include <mat4x4.hpp>

#include "console.h"

//constructor
StaticShader::StaticShader() : Shader() {}
StaticShader::StaticShader(bool generate) : Shader(STATICSHADER_VERTEX_SHADER_PATH, STATICSHADER_FRAGMENT_SHADER_PATH) {
	console::log("Static Shader compiled", 1);
}
