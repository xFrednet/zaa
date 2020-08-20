#include "terrainShader.h"
#include "shader.h"

#include <glew.h>
#include <freeglut.h>

#include "console.h"

//constructor
TerrainShader::TerrainShader() : Shader() {}
TerrainShader::TerrainShader(bool generate) : Shader(TERRAINSHADER_VERTEX_SHADER_PATH, TERRAINSHADER_FRAGMENT_SHADER_PATH) {
	console::log("Terrain Shader compiled", 1);
}