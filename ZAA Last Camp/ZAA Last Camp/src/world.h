#pragma once
#include <glew.h>
#include <freeglut.h>
#include <vec2.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <vector>

#include "terrainRenderer.h"
#include "renderer.h"
#include "entityRenderer.h"
#include "staticShader.h"
#include "shader.h"
#include "entity.h"
#include "rawMesh.h"
#include "texturedMesh.h"
#include "texture.h"
#include "loader.h"
#include "terrainTile.h"
#include "displayManager.h"
#include "tileEntity.h"
#include "terrainShader.h"
#include "camera.h"
#include "light.h"
#include "sprite.h"
#include "terrain.h"

class World {
private:
	void test();
protected:
	
	//shader
	StaticShader staticShader;
	TerrainShader terrainShader;

	//renderer
	TerrainRenderer terrainRenderer;
	EntityRenderer entityRenderer;

	//lists
	std::vector<Entity> entitys;
	std::vector<Light> lights;

	//terrain
	Terrain terrain;

	//util
	Loader loaderClass;

public:
	//constuctor
	World();
	World(Loader &loaderClass, TerrainShader &terrainShader, StaticShader &staticShader, EntityRenderer &entityrenderer, TerrainRenderer &terrainRender);
	
	//gameloop util
	void update();
	void render(Camera &camera);

};