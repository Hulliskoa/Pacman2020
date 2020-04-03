#include "Entity.h"

void Entity::setVelocity(int x, int y) {
	velocity[0] = 0;
	velocity[1] = 0;
}

void Entity::setCoordinates(int* newCoordinates)
{
	coordinates[0] = newCoordinates[0];
	coordinates[1] = newCoordinates[1];
}

void Entity::setEntityType(entityType type)
{
	entityT = type;
}

entityType Entity::getEntityType()
{
	return entityT;
}

void Entity::update(SDL_Window* window) {}

int* Entity::getNewLocation() {
	return nullptr;
}

