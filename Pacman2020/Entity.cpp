#include "Entity.h"

Entity::Entity() {}

Entity::Entity(int xStart, int yStart, int numAnimFrames, SDL_Texture* spriteTexture, int spriteWidth, int spriteHeight) : numFrames(numAnimFrames) {
	startAnimation = std::make_shared<AnimationComponent>(numAnimFrames, spriteTexture, spriteWidth, spriteHeight);
	coordinates[0] = xStart;
	coordinates[1] = yStart;
	velocity[0] = 0;
	velocity[1] = 0;
}

void Entity::setCoordinates(int x, int y)
{
	coordinates[0] = x;
	coordinates[1] = y;
}

void Entity::setEntityType(EntityType type)
{
	entityT = type;
}

EntityType Entity::getEntityType()
{
	if (this == NULL) {
		return EntityType::NOT_DEFINED;
	}

	return entityT;
}

void Entity::setOutSideCage(bool isOutSide)
{
	outsideCage = isOutSide;
}
