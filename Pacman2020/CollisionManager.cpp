#include "CollisionManager.h"

EntityType CollisionManager::collisionCheck(Entity* entityToCheck)
{
	bool collision = false;
	int movementPlane = NULL;
	int oppositePlane = NULL;


	/*
	Checks wich direction the entity is moving and sets movementPlane variable
	*/
	if (entityToCheck->velocity[0] != 0) {
		movementPlane = 0;
	}
	else if (entityToCheck->velocity[1] != 0) {
		movementPlane = 1;
	}

	if (movementPlane == 0) {
		oppositePlane = 1;
	}
	else {
		oppositePlane = 0;
	}

	//Checks if entityToCheck is within hitbox of any other entity on the lvl
	for (auto x : entities) {
		if (x->getEntityType() == entityToCheck->getEntityType()) {
			continue;
		}
		if ((x->coordinates[movementPlane] - hitBoxRadius) <= entityToCheck->coordinates[movementPlane] && entityToCheck->coordinates[movementPlane] <= (x->coordinates[movementPlane] + hitBoxRadius)) {
			if ((x->coordinates[oppositePlane] - hitBoxRadius) <= entityToCheck->coordinates[oppositePlane] && entityToCheck->coordinates[oppositePlane] <= (x->coordinates[oppositePlane] + hitBoxRadius))
			{
				collision = true;
			}
		}
		if (collision) {
			switch (x->getEntityType())
			{
			case EntityType::GHOST:
				return EntityType::GHOST;
				break;
			case EntityType::AFRAID_GHOST:
				return EntityType::AFRAID_GHOST;
				break;
			case EntityType::PELLET:
				return EntityType::PELLET;
				break;
			case EntityType::POWER_PELLET:
				return EntityType::POWER_PELLET;
				break;
			case EntityType::FRUIT:
				return EntityType::FRUIT;
				break;
			case EntityType::WALL:
				return EntityType::WALL;
				break;
			case EntityType::TELEPORT:
				return EntityType::TELEPORT;
				break;
			case EntityType::PACMAN:
				return EntityType::PACMAN;
				break;
			default:
				break;
			}
		}
	}
}


void CollisionManager::addEntity(std::shared_ptr<Entity> entity)
{
	entities.emplace_back(entity);
}


CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}
