#include "Entity.h"

Entity::Entity() {}

Entity::Entity(int xStart, int yStart, int numAnimFrames, SDL_Texture * spriteTexture, int spriteWidth, int spriteHeight) {
	startAnimation = std::make_shared<AnimationComponent>(numAnimFrames, spriteTexture, spriteWidth, spriteHeight);
	coordinates[0] = xStart;
	coordinates[1] = yStart;
	velocity[0] = 0;
	velocity[1] = 0;
}

void Entity::setCoordinates(int* newCoordinates)
{
	coordinates[0] = newCoordinates[0];
	coordinates[1] = newCoordinates[1];
}

void Entity::setEntityType(EntityType type)
{
	entityT = type;
}

EntityType Entity::getEntityType()
{
	return entityT;
}
