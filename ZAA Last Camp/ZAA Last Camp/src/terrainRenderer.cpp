#include "terrainRenderer.h"
#include "renderer.h"

#include <glew.h>
#include <freeglut.h>
#include <mat4x4.hpp>
#include <vector>

#include "shader.h"
#include "matrixMath.h"
#include "world.h"
#include "terrainTile.h"
#include "console.h"
#include "texturedMesh.h"
#include "terrainShader.h"

//constructor
TerrainRenderer::TerrainRenderer() : Renderer() {}
TerrainRenderer::TerrainRenderer(TerrainShader &terrainShader) : Renderer(terrainShader) {}

//render
void TerrainRenderer::render(std::vector<TerrainTile> &terrainTiles, TerrainShader &terrainShader) {
	//error check
	if (terrainTiles.size() == 0) {
		console::err("TerrainRender: the TerrainTile Vector is empty");
	}
	
	//render Loop
	for (unsigned int i = 0; i < terrainTiles.size(); i++) {
		renderTerrainTile(terrainTiles[i], terrainShader);
	}
}
void TerrainRenderer::renderTerrainTile(TerrainTile &terrainTile, TerrainShader &terrainShader) {
	
	TexturedMesh texturedMesh = terrainTile.getTexturedMesh();
	RawMesh rawMesh = texturedMesh.getRawMesh();
	Texture texture = texturedMesh.getTexture();

	//vao
	glBindVertexArray(rawMesh.getVAOID());
	bindVertexAttribs(3);

	//texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureID());

	//matrix loader
	terrainShader.loadTransformationMatrix(terrainTile.getTransformationMatrix());

	//rendering
	glDrawElements(GL_TRIANGLES, rawMesh.getVertexCount(), GL_UNSIGNED_INT, 0);

	//unbinding
	unbindVertexAttribs(3);
	glBindVertexArray(0);

}