#pragma once
#include <vector>
#include "Entity.h"
#include "MovingEntity.h"


class CollisionManager
{
private:
	int hitBoxRadius = 6;
	std::vector<std::shared_ptr<Entity>> entities;

public:
	std::shared_ptr<Entity>  collisionCheck(Entity* entityToCheck);
	void addEntity(std::shared_ptr<Entity> entity);
	CollisionManager();
	~CollisionManager();
};

