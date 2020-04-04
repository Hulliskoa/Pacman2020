#pragma once
#include <vector>
#include "Pacman.h"
#include "Entity.h"

class CollisionManager
{
private:
	std::vector<std::shared_ptr<Entity>> entities;

public:
	void collisionCheck(Entity &entityToCheck);
	void addEntity(Entity &entity);
	CollisionManager();
	~CollisionManager();
};

