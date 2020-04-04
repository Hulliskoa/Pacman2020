#include "CollisionManager.h"

void CollisionManager::collisionCheck(std::shared_ptr<Entity> entityToCheck)
{
	bool collision = false;
	int movementPlane = NULL;
	int oppositePlane = NULL;

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


	for (auto x : entities) {
		if (x->getEntityType() == entityToCheck->getEntityType()) {
			continue;
		}
		for (int i = 0; i < 8; i++) {
			if ((x->coordinates[movementPlane] == (entityToCheck->coordinates[movementPlane] + i)) || (x->coordinates[movementPlane] == (entityToCheck->coordinates[movementPlane] - i))) {
				if (x->coordinates[oppositePlane] == entityToCheck->coordinates[oppositePlane])
				{
					collision = true;
				}
			}
			if (collision) {
				switch (x->getEntityType())
				{
				case GHOST:
					//entity.setVelocity(0, 0);
					std::cout << "hit ghost" << std::endl;
					break;
				case AFRAID_GHOST:break;
				case PELLET:break;
				case POWER_PELLET:break;
				case FRUIT: break;
				case WALL:
					entityToCheck->setVelocity(0, 0);
					break;
				case TELEPORT:
					entityToCheck->setCoordinates(x->getNewLocation());
					break;
				case PACMAN:
					break;
				default:
					break;
				}
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
