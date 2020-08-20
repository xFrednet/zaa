#pragma once
#include <glew.h>
#include <freeglut.h>
#include <mat4x4.hpp>

#include "displayManager.h"
#include "mainRenderer.h"
#include "model.h"
#include "staticShader.h"

class Renderer : public MainRenderer {
public:
	Renderer();
	Renderer(StaticShader &shader);
	void render(Model *model, StaticShader &shader);
};