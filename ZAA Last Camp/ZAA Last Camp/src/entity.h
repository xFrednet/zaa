#pragma once
#include <glew.h>
#include <freeglut.h>
#include <vec3.hpp>
#include <mat4x4.hpp>

#include "matrixMath.h"
#include "texturedMesh.h"

class Entity {
private:
protected:
	TexturedMesh texturedMesh;
	glm::vec3 position;
	glm::vec3 rotation;
	float scale = 1;
public:
	//constructor
	Entity();
	Entity(TexturedMesh &texturedMesh, glm::vec3 position, glm::vec3 rotation, float scale);
	Entity(glm::vec3 position);
	
	//setters
	void setScale(float scale);

	//modifires
	void increasePosition(float dx, float dy, float dz);
	void increaseRotation(float dx, float dy, float dz);

	//getters
	glm::mat4x4 getTransformationMatrix();
	glm::vec3 getPosition();
	glm::vec3 getRotation();
	float getScale();
	TexturedMesh getTexturedMesh();
	GLuint getVAOID();
};