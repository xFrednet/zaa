#include <glew.h>
#include <freeglut.h>
#include <mat4x4.hpp>
#include <iostream>

#include "debug.h"
#include "maths.h"
#include "model.h"
#include "rawModel.h"
#include "renderer.h"
#include "staticShader.h"
#include "texturedModel.h"

Renderer::Renderer() : MainRenderer() {};
Renderer::Renderer(StaticShader &shader) : MainRenderer(shader) {}

void Renderer::render(Model *model, StaticShader &shader) {
	TexturedModel texturedModel = model->texturedModel;
	RawModel rawModel = texturedModel.rawModel;
	ModelTexture modelTexture = texturedModel.modeltexture;
	
	glm::mat4x4 matrix = model->getTransformationMatrix();
	shader.loadTransformationMatrix(matrix);

	glBindVertexArray(rawModel.getVaoID());

	bindVertexAttribs(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, modelTexture.getTextureID());
	glDrawElements(GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);
	
	unbindVertexAttribs(2);
	glBindVertexArray(0);
}