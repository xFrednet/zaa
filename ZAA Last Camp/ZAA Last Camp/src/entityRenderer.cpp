#include "entityRenderer.h"
#include "renderer.h"

#include <glew.h>
#include <freeglut.h>

#include "console.h"
#include "staticShader.h"
#include "entity.h"
#include "texturedMesh.h"
#include "texture.h"
#include "rawMesh.h"

//constructor
EntityRenderer::EntityRenderer() : Renderer() {}
EntityRenderer::EntityRenderer(StaticShader staticShader) : Renderer(staticShader) {}

//render
void EntityRenderer::render(std::vector<Entity> &entitys, StaticShader &staticShader) {
	
	//error check
	if (entitys.size() == 0) {
		console::err("EntityRenderer: Entity vector is empty");
		return;
	}

	//render Values
	GLuint currentVAOID = entitys[0].getVAOID();
	std::vector<Entity> renderList;

	//entity list checker
	for (unsigned int i = 0; i < entitys.size(); i++) {
		
		//checks if the models have the same VAO
		if (entitys[i].getVAOID() == currentVAOID) {
			
			//adds the entity to the renderList
			renderList.push_back(entitys[i]);
		} 
		else {
			//renders current list
			renderEntityType(renderList, staticShader);
			renderList.clear();

			//changes the current VAOID
			currentVAOID = entitys[i].getVAOID();
			
			//adds teh current entity
			renderList.push_back(entitys[i]);
		}
	}

	//renders current list
	renderEntityType(renderList, staticShader);
	
}
void EntityRenderer::renderEntityType(std::vector<Entity> &entitys, StaticShader &staticShader) {
	
	//error check
	if (entitys.size() == 0) {
		console::err("EntityRenderer: Entity vector is empty");
		return;
	}

	TexturedMesh texturedMesh = entitys[0].getTexturedMesh();
	RawMesh rawMesh = texturedMesh.getRawMesh();
	Texture texture = texturedMesh.getTexture();

	//vao
	glBindVertexArray(rawMesh.getVAOID());
	bindVertexAttribs(3);

	//texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureID());
	
	for (unsigned int i = 0; i < entitys.size(); i++) {

		//matrix loader
		staticShader.loadTransformationMatrix(entitys[i].getTransformationMatrix());
		
		//rendering
		glDrawElements(GL_TRIANGLES, rawMesh.getVertexCount(), GL_UNSIGNED_INT, 0);
	}


	//unbinding
	unbindVertexAttribs(3);
	glBindVertexArray(0);
}