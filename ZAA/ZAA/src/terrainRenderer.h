#pragma once
#include <glew.h>
#include <freeglut.h>
#include <mat4x4.hpp>

#include "displayManager.h"
#include "mainRenderer.h"
#include "terrain.h"
#include "staticShader.h"

class TerrainRenderer : public MainRenderer {
public:
	TerrainRenderer();
	TerrainRenderer(StaticShader &shader);
	void render(Terrain *terrain, StaticShader &shader);
};
