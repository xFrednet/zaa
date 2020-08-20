#include <freeglut.h>

#include "modelTexture.h"

ModelTexture::ModelTexture(){}

ModelTexture::ModelTexture(const GLuint &textureID) {
	this->textureID = textureID;
}

GLuint ModelTexture::getTextureID() {
	return textureID;
}