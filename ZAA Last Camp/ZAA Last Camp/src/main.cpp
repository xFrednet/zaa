#include <glew.h>
#include <freeglut.h>
#include <glm.hpp>
#include <iostream>
#include <lodepng.h>
#include <Windows.h>
#include <vector>
#include <vec3.hpp>

#include "console.h"
#include "displayManager.h"
#include "keyboard.h"
#include "loader.h"
#include "mouse.h"

#include "entityRenderer.h"
#include "terrainRenderer.h"

#include "staticShader.h"
#include "terrainShader.h"

#include "texturedMesh.h"
#include "rawMesh.h"
#include "texture.h"
#include "entity.h"
#include "tileEntity.h"
#include "controllableCamera.h"
#include "light.h"
#include "world.h"

//pre
void gameLoop();

//consts
const int UPS = 60;
const int FPS = 60;
const bool printFPSUPS = true;

//render values
StaticShader staticShader;
TerrainShader terrainShader;
EntityRenderer entityRenderer;
TerrainRenderer terrainRenderer;

//used variables
bool running = false;
Loader loaderC;
World world;


//Debug
ControllableCamera camera;
void debug() {
	staticShader = StaticShader(true);
	terrainShader = TerrainShader(true);
	entityRenderer = EntityRenderer(staticShader);
	terrainRenderer = TerrainRenderer(terrainShader);
	
	world = World(loaderC, terrainShader, staticShader, entityRenderer, terrainRenderer);

	camera = ControllableCamera(glm::vec3(16, 0, 16));
}


//util
void stop() {

	//print to console 
	console::log(" ", 1);
	console::log("###############", 1);
	console::log("# Terminating #", 1);
	console::log("###############", 1);
	console::log(" ", 1);

	//clean up
	loaderC.cleanUp();
	staticShader.cleanUp();
	terrainShader.cleanUp();
}
void start() {
	running = true;
	gameLoop();
}
LARGE_INTEGER getFrequenzCounter() {
	LARGE_INTEGER counter;
	if (!QueryPerformanceCounter(&counter)) {
		console::err("Counter Error: ", GetLastError());
	}
	return counter;
}

//gameloop
void update(unsigned long update) {
	displaymanager::update();
	mouse::update();
	camera.update();

	//exit update
	if (isKeyDown(27)) running = false;

	world.update();

}
void render() {
	entityRenderer.prepare();

	world.render(camera);

	displaymanager::updateDisplay();
}
void gameLoop() {
	//Frequency
	LARGE_INTEGER freq;
	if (!QueryPerformanceFrequency(&freq)) {
		console::err("Frequency Error: ", GetLastError());
		system("pause");
		exit(-1);
	}
	
	//counter
	LARGE_INTEGER lastTime = getFrequenzCounter();
	LARGE_INTEGER timer = getFrequenzCounter();

	float freq_f = (float)freq.QuadPart / FPS;
	float freq_u = (float)freq.QuadPart / UPS;
	float delta_f = 0;
	float delta_u = 0;
	unsigned long frames = 0;
	unsigned long updates = 0;
	unsigned long lastUpdates = 0;

	while (running) {
		LARGE_INTEGER now = getFrequenzCounter();
		delta_u += (now.QuadPart - lastTime.QuadPart) / freq_u;
		delta_f += (now.QuadPart - lastTime.QuadPart) / freq_f;
		lastTime.QuadPart = now.QuadPart;

		//update
		if (delta_u >= 1) {
			update(updates);
			delta_u--;
			updates++;
		}

		//frames
		if (delta_f >= 1) {
			render();
			delta_f--;
			frames++;
		}

		Sleep(1);
		if ((now.QuadPart - timer.QuadPart) >= freq.QuadPart) {
			if (printFPSUPS) {
				std::cout << "[INFO] FPS: " << frames << "| UPS: " << updates - lastUpdates << std::endl;
			}

			timer.QuadPart += freq.QuadPart;
			frames = 0;
			lastUpdates = updates;
		}
	}
	stop();
}

//main
int main(int argv, char **argc) {
	//Debug Info
	console::logVersions();

	//create Window
	displaymanager::createWindow(argv, argc);

	//start
	debug();
	start();

	return 0;
}