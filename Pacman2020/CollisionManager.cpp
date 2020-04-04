#include "CollisionManager.h"

void CollisionManager::collisionCheck(Entity entity)
{
	for (auto x : entities) {
		if (x.getEntityType() == PACMAN) {
			continue;
		}
		if ((entity.coordinates[0] == x.coordinates[0]) && (entity.coordinates[1] == x.coordinates[1])) {


			switch (x.getEntityType())
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
				entity.setVelocity(0, 0);
				break;
			case TELEPORT: 
				entity.setCoordinates(x.getNewLocation());
				break;
			default:
				break;
			}
		}
	}
}
