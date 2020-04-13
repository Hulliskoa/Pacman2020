#include "Entity.h"

Entity::Entity() {}
/*
Entity::Entity(SDL_Renderer* renderer, int x, int y, int numAnimFrames, SDL_Surface* mainSpriteSheet) {
	startAnimation = std::make_shared<AnimationComponent>(renderer, numAnimFrames);
	coordinates[0] = x;
	coordinates[1] = y;
	velocity[0] = 0;
	velocity[1] = 0;

	if (!startAnimation->loadFromFile(mainSpriteSheet)) {
		std::cout << "could not load spritesheet" << std::endl;
	}

}*/

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
