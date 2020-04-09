#include "MovingEntity.h"

void MovingEntity::setVelocity(int x, int y) {
	velocity[0] = x;
	velocity[1] = y;
}

void MovingEntity::update() {
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

MovingEntity::MovingEntity(SDL_Renderer* renderer, int x, int y, int numAnimFrames, SDL_Surface* mainSpriteSheet) : velocity{ 0,0 }, numFrames(numAnimFrames)
{
	
	coordinates[0] = x;
	coordinates[1] = y;
	leftAnimation = std::make_shared<AnimationComponent>(renderer, numFrames);
	rightAnimation = std::make_shared<AnimationComponent>(renderer, numFrames);
	upAnimation = std::make_shared<AnimationComponent>(renderer, numFrames);
	downAnimation = std::make_shared<AnimationComponent>(renderer, numFrames);
	startAnimation = std::make_shared<AnimationComponent>(renderer, numFrames);


	if (!leftAnimation->loadFromFile(mainSpriteSheet))
	{
		std::cout << "Failed to load sprite sheet texture!" << std::endl;

	}	if (!rightAnimation->loadFromFile(mainSpriteSheet))
	{
		std::cout << "Failed to load sprite sheet texture!" << std::endl;

	}	if (!upAnimation->loadFromFile(mainSpriteSheet))
	{
		std::cout << "Failed to load sprite sheet texture!" << std::endl;

	}	if (!downAnimation->loadFromFile(mainSpriteSheet))
	{
		std::cout << "Failed to load sprite sheet texture!" << std::endl;

	}	if (!startAnimation->loadFromFile(mainSpriteSheet))
	{
		std::cout << "Failed to load sprite sheet texture!" << std::endl;

	}
}

MovingEntity::MovingEntity() : velocity{ 0,0 } {}

