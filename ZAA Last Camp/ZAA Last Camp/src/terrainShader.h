#pragma once
#include "shader.h"

#include <glew.h>
#include <freeglut.h>

#define TERRAINSHADER_VERTEX_SHADER_PATH "shader\\terrainVertex.Shader"
#define TERRAINSHADER_FRAGMENT_SHADER_PATH "shader\\terrainFragment.Shader"

class TerrainShader : public Shader {
private:
protected:
public:
	//constructor
	TerrainShader();
	TerrainShader(bool generate);
};