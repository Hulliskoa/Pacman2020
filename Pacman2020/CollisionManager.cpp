#include "CollisionManager.h"

std::shared_ptr<Entity> CollisionManager::collisionCheck(Entity* entityToCheck)
{
	bool collision = false;
	int movementPlane = NULL;
	int oppositePlane = NULL;

	//Checks which direction the entity is moving and sets movementPlane based on that
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

	//Checks if entityToCheck is within hitbox of any other entity on the map, returns value to be used for entity's updatefunction
	for (auto x : entities) {
		if (x->getEntityType() == entityToCheck->getEntityType()) {
			continue;
		}
		//Use hitbox dimensions to check if an entity is within range
		if ((x->coordinates[movementPlane] - hitBoxRadius) <= entityToCheck->coordinates[movementPlane] && entityToCheck->coordinates[movementPlane] <= (x->coordinates[movementPlane] + hitBoxRadius)) {
			if ((x->coordinates[oppositePlane] - hitBoxRadius) <= entityToCheck->coordinates[oppositePlane] && entityToCheck->coordinates[oppositePlane] <= (x->coordinates[oppositePlane] + hitBoxRadius))
			{
				collision = true;
			}
		}
		if (collision) {
			std::cout << "Hit: " << std::endl;
			return x;
		}
		else {
			return nullptr;
		}
	}
}

void CollisionManager::addEntity(std::shared_ptr<Entity> entity)
{
	entities.emplace_back(entity);
}

CollisionManager::CollisionManager(){}

CollisionManager::~CollisionManager(){}
