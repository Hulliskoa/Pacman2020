#include "Entity.h"

void Entity::setVelocity(int x, int y) {
	velocity[0] = x;
	velocity[1] = y;
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

void Entity::update() {
	//teleports entity when going outside window
	if (coordinates[0] > 230) {
		coordinates[0] = -10;
	}
	if (coordinates[1] > 295) {
		coordinates[1] = -10;
	}
	if (coordinates[0] < -10) {
		coordinates[0] = 230;
	}
	if (coordinates[1] < -10) {
		coordinates[1] = 295;
	}

}

Entity::Entity(SDL_Renderer* renderer, int x, int y, int numFrames, SDL_Surface* mainSpriteSheet) : velocity{ 0,0 }, coordinates{ x,y }, numFrames(numFrames), spriteSheet(mainSpriteSheet)
{
	//TODO: laste opp spritesheet en gang

	leftAnimation = std::make_shared<AnimationComponent>(renderer, numFrames);
	rightAnimation = std::make_shared<AnimationComponent>(renderer, numFrames);
	upAnimation = std::make_shared<AnimationComponent>(renderer, numFrames);
	downAnimation = std::make_shared<AnimationComponent>(renderer, numFrames);
	startAnimation = std::make_shared<AnimationComponent>(renderer, numFrames);


	if (!leftAnimation->loadFromFile(spriteSheet))
	{
		std::cout << "Failed to load sprite sheet texture!" << std::endl;

	}	if (!rightAnimation->loadFromFile(spriteSheet))
	{
		std::cout << "Failed to load sprite sheet texture!" << std::endl;

	}	if (!upAnimation->loadFromFile(spriteSheet))
	{
		std::cout << "Failed to load sprite sheet texture!" << std::endl;

	}	if (!downAnimation->loadFromFile(spriteSheet))
	{
		std::cout << "Failed to load sprite sheet texture!" << std::endl;

	}	if (!startAnimation->loadFromFile(spriteSheet))
	{
		std::cout << "Failed to load sprite sheet texture!" << std::endl;

	}
}

Entity::Entity() :coordinates{ 0,0 }, velocity{ 0,0 }, spriteSheet(nullptr) {}

