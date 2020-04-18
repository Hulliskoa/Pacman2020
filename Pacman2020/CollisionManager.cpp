#include "CollisionManager.h"

std::vector<std::shared_ptr<Entity>> CollisionManager::collisionCheck(std::shared_ptr<Entity> entityToCheck)
{
	//std::thread t1(collisionCheckMoving(entityToCheck));
	entitiesCollidedWith.clear();



	auto t1 = std::async(&CollisionManager::collisionCheckStationary, this, entityToCheck);
	auto t2 = std::async(&CollisionManager::collisionCheckMoving, this, entityToCheck);

	entitiesCollidedWith.emplace_back(t1.get());
	entitiesCollidedWith.emplace_back(t2.get());

	return entitiesCollidedWith;
}

std::shared_ptr<Entity> CollisionManager::collisionCheckMoving(std::shared_ptr<Entity> entityToCheck)
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



	for (auto x : movingEntities) {

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
			if (collisionBoxStart >= x->coordinates[movementPlane] && x->coordinates[movementPlane] >= collisionBoxEnd) {
				if ((collisionBoxEdge1 <= x->coordinates[oppositePlane]) && (collisionBoxEdge2 >= x->coordinates[oppositePlane])) {
					collision = true;
				}
			}
		}
		else {
			if (collisionBoxStart <= x->coordinates[movementPlane] && x->coordinates[movementPlane] <= collisionBoxEnd) {
				if ((collisionBoxEdge1 <= x->coordinates[oppositePlane]) && (collisionBoxEdge2 >= x->coordinates[oppositePlane])) {
					collision = true;
				}
			}
		}
		//returns the object that the entity collided with
		if (collision) {
			return x;
		}
	}
	return nullptr;
}

std::shared_ptr<Entity> CollisionManager::collisionCheckStationary(std::shared_ptr<Entity> entityToCheck)
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
	for (auto x : stationaryEntities) {

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
	return nullptr;

}

void CollisionManager::addEntity(std::shared_ptr<Entity> entity)
{
	stationaryEntities.emplace_back(entity);
}

void CollisionManager::addMovingEntity(std::shared_ptr<Entity> entity)
{
	movingEntities.emplace_back(entity);
}

bool CollisionManager::checkIntersection(std::shared_ptr<Entity> entityToCheck)
{
	for (auto x : stationaryEntities) {
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
	stationaryEntities.clear();
}

CollisionManager::CollisionManager() {}

CollisionManager::~CollisionManager() {}
