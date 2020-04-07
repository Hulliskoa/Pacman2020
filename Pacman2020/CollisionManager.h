#pragma once
#include <vector>
#include "Entity.h"


class CollisionManager
{
private:
	int hitBoxRadius = 4;
	std::vector<std::shared_ptr<Entity>> entities;

public:
	void collisionCheck(std::shared_ptr<Entity> entityToCheck);
	void addEntity(std::shared_ptr<Entity> entity);
	CollisionManager();
	~CollisionManager();
};

