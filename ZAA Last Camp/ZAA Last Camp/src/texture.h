#pragma once
#include <glew.h>
#include <freeglut.h>

class Texture {
private:
	GLuint textureID = 0;
public:
	//constructor
	Texture();
	Texture(GLuint textureID);
	Texture(const char *filepath);

	//getters
	GLuint getTextureID();
};