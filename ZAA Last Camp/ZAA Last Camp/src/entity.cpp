#include "entity.h"

#include <glew.h>
#include <freeglut.h>
#include <vec3.hpp>
#include <mat4x4.hpp>

#include "matrixMath.h"
#include "texturedMesh.h"

//constructor
Entity::Entity() {}
Entity::Entity(glm::vec3 position) {
	this->position = position;
	this->scale = 0;
}
Entity::Entity(TexturedMesh &texturedMesh, glm::vec3 position, glm::vec3 rotation, float scale) {
	this->texturedMesh = texturedMesh;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

//setters
void Entity::setScale(float scale) {
	this->scale = scale;
}

//modifires
void Entity::increasePosition(float dx, float dy, float dz) {
	position.x += dx;
	position.y += dy;
	position.z += dz;
}
void Entity::increaseRotation(float rx, float ry, float rz) {
	rotation.x += rx;
	rotation.y += ry;
	rotation.z += rz;
}

//getters
glm::mat4x4 Entity::getTransformationMatrix() {
	return matrixmath::getTransformationMatrix(position, rotation, scale);
}
glm::vec3 Entity::getPosition() {
	return position;
}
glm::vec3 Entity::getRotation() {
	return rotation;
}
float Entity::getScale() {
	return scale;
}
TexturedMesh Entity::getTexturedMesh() {
	return texturedMesh;
}
GLuint Entity::getVAOID() {
	return texturedMesh.getRawMesh().getVAOID();
}