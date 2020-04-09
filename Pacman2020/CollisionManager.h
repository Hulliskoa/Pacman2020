#pragma once
#include <vector>
#include "MovingEntity.h"


class CollisionManager
{
private:
	int hitBoxRadius = 4;
	std::vector<std::shared_ptr<MovingEntity>> entities;

public:
	std::shared_ptr<MovingEntity>  collisionCheck(MovingEntity * entityToCheck);
	void addEntity(std::shared_ptr<MovingEntity> entity);
	CollisionManager();
	~CollisionManager();
};

