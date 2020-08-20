#include <glew.h>
#include <freeglut.h>
#include <glm.hpp>
#include <string.h>

#include "camera.h"
#include "controlableCamera.h"
#include "debug.h"
#include "displayManager.h"
#include "entity.h"
#include "keyboard.h"
#include "loader.h"
#include "mainRenderer.h"
#include "model.h"
#include "modelTexture.h"
#include "rawModel.h"
#include "renderer.h"
#include "shader.h"
#include "sprite.h"
#include "staticShader.h"
#include "terrain.h"
#include "terrainRenderer.h"
#include "texturedModel.h"

//Tests

float vertices[] = {
	-0.5f,0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f,0.5f,-0.5f,

	-0.5f,0.5f,0.5f,
	-0.5f,-0.5f,0.5f,
	0.5f,-0.5f,0.5f,
	0.5f,0.5f,0.5f,

	0.5f,0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,0.5f,
	0.5f,0.5f,0.5f,

	-0.5f,0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,0.5f,
	-0.5f,0.5f,0.5f,

	-0.5f,0.5f,0.5f,
	-0.5f,0.5f,-0.5f,
	0.5f,0.5f,-0.5f,
	0.5f,0.5f,0.5f,

	-0.5f,-0.5f,0.5f,
	-0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,0.5f

};
float textureCoords[] = {

	0.00000f,0.00000f,
	0.00000f,1.00000f,
	1.00000f,1.00000f,
	1.00000f,0.00000f,
	0.00000f,0.00000f,
	0.00000f,1.00000f,
	1.00000f,1.00000f,
	1.00000f,0.00000f,
	0.00000f,0.00000f,
	0.00000f,1.00000f,
	1.00000f,1.00000f,
	1.00000f,0.00000f,
	0.00000f,0.00000f,
	0.00000f,1.00000f,
	1.00000f,1.00000f,
	1.00000f,0.00000f,
	0.00000f,0.00000f,
	0.00000f,1.00000f,
	1.00000f,1.00000f,
	1.00000f,0.00000f,
	0.00000f,0.00000f,
	0.00000f,1.00000f,
	1.00000f,1.00000f,
	1.00000f,0.00000f


};
int indices[] = {
	0,1,3,
	3,1,2,
	4,5,7,
	7,5,6,
	8,9,11,
	11,9,10,
	12,13,15,
	15,13,14,
	16,17,19,
	19,17,18,
	20,21,23,
	23,21,22

};

Loader loader;
ControlableCamera camera(glm::vec3(5, 2, 5));
StaticShader staticShader;
Renderer renderer;
TerrainRenderer terrainRenderer;
bool running = true;
const int UPS = 60;
const int FPS = 70;

//DEBUG
Model model;
Model model2;
Model model3;
Model model4;
Model tmodel;
Model testmodel2;
Terrain terrain;
void setupDebug() {
	staticShader = StaticShader(true);
	renderer = Renderer(staticShader);
	terrainRenderer = TerrainRenderer(staticShader);
	
	TexturedModel tModel = loader.loadModel("cube.obj");
	model = Model(tModel, glm::vec3(0, 0, 0), 0.1f);
	model2 = Model(tModel, glm::vec3(10, 0, 0), 0.1f);
	model3 = Model(tModel, glm::vec3(0, 0, 10), 0.1f);
	model4 = Model(tModel, glm::vec3(10, 0, 10), 0.1f);

	int x = 0, y = 0;
	terrain = Terrain("depthMap.png", x, y, loader);
	
	TexturedModel tModel2 = loader.loadModel("Blue_Plastic_Bin.obj");
	tmodel = Model(tModel2, glm::vec3(5, 1, 5), 1);

	TexturedModel teModel2 = loader.loadModel("Wooden_Cup.obj");
	testmodel2 = Model(teModel2, glm::vec3(5, 3, 5), 0.1f);

}
//DEBUG ENDE

void stop() {
	console::log(" ", 1);
	if (DEBUG >= 2) {
		std::cout << "###############" << std::endl;
		std::cout << "# Terminating #" << std::endl;
		std::cout << "###############" << std::endl;
		std::cout << " " << std::endl;
	}

	staticShader.cleanUp();
	loader.cleanUp();
}

void update() {
	glutMainLoopEvent();
	camera.update();
	model.increaseRotation(-0.1f, -0.1f, -0.1f);
	model2.increaseRotation(-0.1f, -0.1f, -0.1f);
	model3.increaseRotation(-0.1f, -0.1f, -0.1f);
	model4.increaseRotation(-0.1f, -0.1f, -0.1f);
	
	if (isKeyDown(27) == 1) {
		running = false;
	}
}

void render() {
	renderer.prepare();
	staticShader.start();
	staticShader.loadViewMatrix(camera.getViewMatrix());

	renderer.render(&model, staticShader);
	renderer.render(&model2, staticShader);
	renderer.render(&model3, staticShader);
	renderer.render(&model4, staticShader);
	renderer.render(&tmodel, staticShader);
	renderer.render(&testmodel2, staticShader);
	terrainRenderer.render(&terrain, staticShader);

	staticShader.stop();
	DisplayManager::updateWindow();
}

void getPerformanceCounter(LARGE_INTEGER *counter) {
	if (!QueryPerformanceCounter(counter)) {
		console::err("Unable to get the PerformanceCounter with following Error ", GetLastError());
	}
}

void gameLoop() {
	LARGE_INTEGER lastTime;
	getPerformanceCounter(&lastTime);
	LARGE_INTEGER timer;
	getPerformanceCounter(&timer);
	LARGE_INTEGER frequency;
	if (!QueryPerformanceFrequency(&frequency)) console::err("Unable to get the PerformanceFrequency with following Error ", GetLastError());
	
	//updates
	float delta_updates = 0;
	float fq_updates = frequency.QuadPart / UPS;
	int updates = 0;

	//frames
	float delta_frames = 0;
	float fq_frames = frequency.QuadPart / FPS;
	int frames = 0;

	while (running) {
		LARGE_INTEGER now;
		getPerformanceCounter(&now);
		delta_updates += (now.QuadPart - lastTime.QuadPart) / fq_updates;
		delta_frames += (now.QuadPart - lastTime.QuadPart) / fq_frames;
		lastTime.QuadPart = now.QuadPart;

		//update
		if (delta_updates >= 1) {
			update(); 
			updates++;
			delta_updates--;
		}

		//frame
		if (delta_frames >= 1) {
			render();
			frames++;
			delta_frames--;
		}
		
		Sleep(10);
		if ((lastTime.QuadPart - timer.QuadPart) >= frequency.QuadPart) {
			console::log("FPS: ", frames, "| UPS: ", updates, 4);
			timer.QuadPart += frequency.QuadPart;
			frames = 0;
			updates = 0;
		}
	}
	stop();
}

int main(int argv, char** argc) {
	//Debug Info
	if (DEBUG > 0) {
		std::cout << ">Debug Level :		" << DEBUG << std::endl;
		std::cout << ">GLEW Version:		" << GLEW_VERSION << std::endl;
		std::cout << ">FreeGLUT Version:	" << GLUT_VERSION << std::endl;
		std::cout << ">GLM Version:		" << GLM_VERSION << std::endl;
		std::cout << ">OpenGL Version		" << GL_VERSION << std::endl;
		std::cout << " " << std::endl;
	}

	//create Window
	DisplayManager::createWindow(argv, argc);
	
	setupDebug();
	gameLoop();

	//system("pause");
	return 0;
}

