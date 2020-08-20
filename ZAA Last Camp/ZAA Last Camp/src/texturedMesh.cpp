#include "texturedMesh.h"

#include "rawMesh.h"
#include "texture.h"

//constructor
TexturedMesh::TexturedMesh() {}
TexturedMesh::TexturedMesh(RawMesh &rawMesh, Texture &texture) {
	this->rawMesh = rawMesh;
	this->texture = texture;
}

//getters
RawMesh TexturedMesh::getRawMesh() {
	return rawMesh;
}
Texture TexturedMesh::getTexture() {
	return texture;
}