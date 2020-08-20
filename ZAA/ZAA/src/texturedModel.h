#pragma once

#include "modelTexture.h"
#include "rawModel.h"

class TexturedModel {
public:
	RawModel rawModel;
	ModelTexture modeltexture;
	TexturedModel();
	TexturedModel(RawModel &rawModel, ModelTexture &modeltexture);
};
