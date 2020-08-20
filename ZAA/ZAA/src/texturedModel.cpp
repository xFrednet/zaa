#include "rawModel.h"
#include "modelTexture.h"
#include "texturedModel.h"

TexturedModel::TexturedModel() {}
TexturedModel::TexturedModel(RawModel &rawModel, ModelTexture &modeltexture) {
	this->rawModel = rawModel;
	this->modeltexture = modeltexture;
}