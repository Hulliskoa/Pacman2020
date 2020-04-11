#pragma once
#include <vector>
#include "Entity.h"
#include "MovingEntity.h"

/**
	CollisionManger class does collisionchecking on behalf of all the MovingEntity objects
*/
class CollisionManager
{
private:
	int hitBoxRadius = 8;
	std::vector<std::shared_ptr<Entity>> entities;

public:
	std::shared_ptr<Entity>  collisionCheck(Entity* entityToCheck);
	void addEntity(std::shared_ptr<Entity> entity);
	CollisionManager();
	~CollisionManager();
};

