#include "MovingEntity.h"

void MovingEntity::setVelocity(int x, int y) {
	velocity[0] = x;
	velocity[1] = y;
}

void MovingEntity::update() {

	//teleports entity back when going outside window
	if (coordinates[1] < -8) {
		coordinates[1] = 250;
	}
	if (coordinates[0] > 240) {
		coordinates[0] = -4;
	}
	if (coordinates[1] > 280) {
		coordinates[1] = -8;
	}
	if (coordinates[0] < -4) {
		coordinates[0] = 240;
	}


}

void MovingEntity::increaseSpeed()
{
	m_normalSpeed += 2;
}

void MovingEntity::setBaseSpeed(int newSpeed)
{
	m_normalSpeed = newSpeed;
}

MovingEntity::MovingEntity(int xStart, int yStart, int numAnimFrames, SDL_Texture* mainSpriteSheet, int textureWidth, int textureHeight)
{
	numFrames = numAnimFrames;
	velocity[0] = 0;
	velocity[1] = 0;
	coordinates[0] = xStart;
	coordinates[1] = yStart;
	rightAnimation = std::make_shared<AnimationComponent>(numFrames, mainSpriteSheet, textureWidth, textureHeight);
	leftAnimation = std::make_shared<AnimationComponent>(numFrames, mainSpriteSheet, textureWidth, textureHeight);
	upAnimation = std::make_shared<AnimationComponent>(numFrames, mainSpriteSheet, textureWidth, textureHeight);
	downAnimation = std::make_shared<AnimationComponent>(numFrames, mainSpriteSheet, textureWidth, textureHeight);
	startAnimation = std::make_shared<AnimationComponent>(numFrames, mainSpriteSheet, textureWidth, textureHeight);
}

MovingEntity::MovingEntity() {}

int MovingEntity::getSpeed()
{
	return m_normalSpeed;
}


