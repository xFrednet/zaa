#include <vec3.hpp>

#include "entity.h"

Entity::Entity() {}
Entity::Entity(glm::vec3 &position) {
	this->position = position;
}
void Entity::update() {}