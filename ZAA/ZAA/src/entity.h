#pragma once
#include <vec3.hpp>

class Entity {
public:
	
	glm::vec3 position;
	glm::vec3 motion;
	
	Entity();
	Entity(glm::vec3 &position);

	virtual void update();
};