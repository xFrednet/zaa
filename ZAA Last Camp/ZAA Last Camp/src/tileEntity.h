#pragma once
#include "entity.h"

#include <vec3.hpp>

#include "texturedMesh.h"

class TileEntity : public Entity {
private:
protected:
public:
	//constructor
	TileEntity();
	TileEntity(TexturedMesh &texturedMesh, glm::vec3 position, glm::vec3 rotation, float scale);

};