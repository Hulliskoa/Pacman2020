#include "CollisionManager.h"

std::shared_ptr<Entity> CollisionManager::collisionCheck(std::shared_ptr<Entity> entityToCheck)
{
	bool collision = false;
	int flip = 1;
	int movementPlane = 0;
	int oppositePlane = 0;

	//Checks which direction the entity is moving and sets movementPlane based on that
	if (entityToCheck->velocity[0] != 0) {
		movementPlane = 0;
		oppositePlane = 1;
	}
	else if (entityToCheck->velocity[1] != 0) {
		movementPlane = 1;
		oppositePlane = 0;
	}
	// if standing still
	if ((movementPlane == 0) && (oppositePlane == 0)) {
		return nullptr;
	}

	//Checks if entityToCheck is within hitbox of any other entity on the map, returns value to be used in entity's update function
	for (auto x : entities) {

		if (x->getEntityType() == entityToCheck->getEntityType()) {
			continue;
		}

		//flips collision box to negative to be able to check for collision in all directions
		if (entityToCheck->velocity[movementPlane] < 0) {
			flip = -1;
		}
		int collisionBoxStart = entityToCheck->coordinates[movementPlane];
		int collisionBoxEnd = (entityToCheck->coordinates[movementPlane]) + ((hitBoxRadius + hitBoxRadius / 2) * flip);
		int collisionBoxEdge1 = (entityToCheck->coordinates[oppositePlane]) - (hitBoxRadius);
		int collisionBoxEdge2 = (entityToCheck->coordinates[oppositePlane]) + (hitBoxRadius);
		//Use hitbox dimensions to check if an entity is within range

		//Use flip to determine in what directon to look for collision
		if (flip < 0) {
			if (collisionBoxStart > x->coordinates[movementPlane] && x->coordinates[movementPlane] > collisionBoxEnd) {
				if ((collisionBoxEdge1 < x->coordinates[oppositePlane]) && (collisionBoxEdge2 > x->coordinates[oppositePlane])) {
					collision = true;
				}
			}
		}
		else {
			if (collisionBoxStart < x->coordinates[movementPlane] && x->coordinates[movementPlane] < collisionBoxEnd) {
				if ((collisionBoxEdge1 < x->coordinates[oppositePlane]) && (collisionBoxEdge2 > x->coordinates[oppositePlane])) {
					collision = true;
				}
			}
		}
		//returns the object that the entity collided with
		if (collision) {
			return x;
		}
	}
}

void CollisionManager::addEntity(std::shared_ptr<Entity> entity)
{
	entities.emplace_back(entity);
}

bool CollisionManager::checkIntersection(std::shared_ptr<Entity> entityToCheck)
{
	for (auto x : entities) {
		if (x->getEntityType() == EntityType::INTERSECTION) {
			if ((x->coordinates[0] == entityToCheck->coordinates[0]) && (x->coordinates[1] == entityToCheck->coordinates[1])) {
				return true;
			}
		}
	}
	return false;
}

void CollisionManager::clearEntityArray()
{
	entities.clear();
}

CollisionManager::CollisionManager() {}

CollisionManager::~CollisionManager() {}
