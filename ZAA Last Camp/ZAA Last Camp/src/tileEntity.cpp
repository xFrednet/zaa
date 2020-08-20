#include "tileEntity.h"
#include "entity.h"

#include <vec3.hpp>

#include "texturedMesh.h"

//constructor
TileEntity::TileEntity() : Entity() {}
TileEntity::TileEntity(TexturedMesh &texturedMesh, glm::vec3 position, glm::vec3 rotation, float scale) : Entity(texturedMesh, position, rotation, scale) {}