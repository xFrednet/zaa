#pragma once
#include <freeglut.h>

class ModelTexture {
private:
	GLuint textureID;
public:

	ModelTexture();
	ModelTexture(const GLuint &textureID);
	GLuint getTextureID();
};
