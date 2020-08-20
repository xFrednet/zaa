#include "light.h"

#include <glew.h>
#include <freeglut.h>
#include <vec3.hpp>

Light::Light() {}
Light::Light(glm::vec3 position, glm::vec3 color) {
	this->position = position;
	this->color = color;
}

//setters
void Light::setPosition(glm::vec3 position) {
	this->position = position;
}
void Light::setColor(glm::vec3 color) {
	this->color = color;
}

//getters
glm::vec3 Light::getPosition() {
	return position;
}
glm::vec3 Light::getColor() {
	return color;
}