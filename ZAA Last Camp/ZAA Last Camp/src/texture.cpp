#include "texture.h"

#include <glew.h>
#include <freeglut.h>

#include "loader.h"

//constructor
Texture::Texture() {}
Texture::Texture(GLuint textureID) {
	this->textureID = textureID;
}
Texture::Texture(const char *filename) {

}

//getters
GLuint Texture::getTextureID() {
	return textureID;
}