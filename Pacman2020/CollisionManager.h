#pragma once
#include <vector>
#include "Pacman.h"
#include "Entity.h"

class CollisionManager
{
private:
	std::vector<Entity> entities;

public:
	void collisionCheck(Entity pacman);
};

