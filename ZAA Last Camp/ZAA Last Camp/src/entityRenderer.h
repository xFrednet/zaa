#pragma once
#include "renderer.h"

#include <glew.h>
#include <freeglut.h>
#include <vector>

#include "staticShader.h"
#include "entity.h"

class EntityRenderer : public Renderer {
protected:
	//render
	void renderEntityType(std::vector<Entity> &entitys, StaticShader &staticShader);
public:
	//constructor
	EntityRenderer();
	EntityRenderer(StaticShader staticShader);

	//render
	void render(std::vector<Entity> &entitys, StaticShader &staticShader);
}; 