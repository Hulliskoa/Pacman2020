#pragma once
#include <vector>
#include "Pacman.h"
#include "Entity.h"

class CollisionManager
{
private:
	std::vector<std::shared_ptr<Entity>> entities;

public:
	void collisionCheck(std::shared_ptr<Entity> entityToCheck);
	void addEntity(std::shared_ptr<Entity> entity);
	CollisionManager();
	~CollisionManager();
};

