#include "MovingEntity.h"

void MovingEntity::setVelocity(int x, int y) {
	velocity[0] = x;
	velocity[1] = y;
}

void MovingEntity::update() {
	//teleports entity when going outside window
	if (coordinates[0] > 250) {
		coordinates[0] = -8;
	}
	if (coordinates[1] > 295) {
		coordinates[1] = -8;
	}
	if (coordinates[0] < -8) {
		coordinates[0] = 250;
	}
	if (coordinates[1] < -8) {
		coordinates[1] = 320;
	}

}

MovingEntity::MovingEntity(SDL_Renderer* renderer, int x, int y, int numAnimFrames, SDL_Surface* mainSpriteSheet) : numFrames(numAnimFrames)
{
	velocity[0] = 0;
	velocity[1] = 0;
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

MovingEntity::MovingEntity(){}


