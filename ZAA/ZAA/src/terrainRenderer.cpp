#include <iostream>
#include <glew.h>
#include <freeglut.h>
#include <mat4x4.hpp>


#include "mainRenderer.h"
#include "terrain.h"
#include "terrainRenderer.h"
#include "staticShader.h"

TerrainRenderer::TerrainRenderer() : MainRenderer() {}
TerrainRenderer::TerrainRenderer(StaticShader &shader) : MainRenderer(shader) {}

void TerrainRenderer::render(Terrain *terrain, StaticShader &shader) {
	RawModel rawModel = terrain->rawModel;

	glm::mat4x4 matrix = terrain->getTransformationMatrix();
	shader.loadTransformationMatrix(matrix);
	
	glBindVertexArray(rawModel.getVaoID());

	bindVertexAttribs(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, terrain->textureID);
	glDrawElements(GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);

	unbindVertexAttribs(2);
	glBindVertexArray(0);
}