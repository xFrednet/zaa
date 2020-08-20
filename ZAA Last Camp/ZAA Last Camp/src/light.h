#pragma once
#include <glew.h>
#include <freeglut.h>
#include <vec3.hpp>

class Light {
private:
protected:
	glm::vec3 position;
	glm::vec3 color;
public:
	//constructor
	Light();
	Light(glm::vec3 position, glm::vec3 color);

	//setters
	void setPosition(glm::vec3 position);
	void setColor(glm::vec3 color);

	//getters
	glm::vec3 getPosition();
	glm::vec3 getColor();

};