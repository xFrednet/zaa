#include "world.h"

#include <glew.h>
#include <freeglut.h>
#include <vec2.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <vector>

#include "renderer.h"
#include "entityRenderer.h"
#include "staticShader.h"
#include "terrainRenderer.h"
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
#include "sprite.h"
#include "spriteTile.h"
#include "terrain.h"

//test
void World::test() {
	//terrain
	terrain = Terrain("world\\map.png", loaderClass, terrainShader, terrainRenderer);

	//objModell
	TexturedMesh tMesh = loaderClass.loadMesh("models\\fox.obj", "texture\\fox.png");
	TileEntity e = TileEntity(tMesh, glm::vec3(8, 2, 8), glm::vec3(0, 180, 0), 1);
	entitys.push_back(e);

	//lights
	Light light(glm::vec3(0, 1, -5), glm::vec3(1, 1, 1));
	lights.push_back(light);
}

//constuctor
World::World() {}
World::World(Loader &loaderClass, TerrainShader &terrainShader, StaticShader &staticShader, EntityRenderer &entityrenderer, TerrainRenderer &terrainRender) {
	//shaders
	this->staticShader = staticShader;
	this->terrainShader = terrainShader;
	
	//renderer
	this->entityRenderer = entityrenderer;
	this->terrainRenderer = terrainRenderer;

	this->loaderClass = loaderClass;

	test();
}

//gameloop util
void World::update() {
	
}
void World::render(Camera &camera) {

	lights[0].setPosition(camera.getPosition());

	staticShader.start();
	staticShader.loadLight(lights[0]);
	staticShader.loadViewMatrix(camera.getViewMatrix());
	entityRenderer.render(entitys, staticShader);
	staticShader.stop();

	terrain.render(camera);
}