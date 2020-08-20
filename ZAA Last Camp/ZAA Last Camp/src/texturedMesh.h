#pragma once
#include "rawMesh.h"
#include "texture.h"

class TexturedMesh {
private:
	RawMesh rawMesh;
	Texture texture;
public:
	//constructor
	TexturedMesh();
	TexturedMesh(RawMesh &rawMesh, Texture &texture);

	//getters
	RawMesh getRawMesh();
	Texture getTexture();
};