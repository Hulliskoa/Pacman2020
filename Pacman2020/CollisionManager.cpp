#include "CollisionManager.h"

void CollisionManager::collisionCheck(Entity &entityToCheck)
{
	for (auto x : entities) {
		if (x->getEntityType() == PACMAN) {
			continue;
		}
		if ((entityToCheck.coordinates[0] == x->coordinates[0]) && (entityToCheck.coordinates[1] == x->coordinates[1])) {


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
				entityToCheck.setVelocity(0, 0);
				break;
			case TELEPORT:
				entityToCheck.setCoordinates(x->getNewLocation());
				break;
			default:
				break;
			}
		}
	}
}

void CollisionManager::addEntity(Entity &entity)
{
	entities.push_back(std::make_shared<Entity>(entity));
}

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}
