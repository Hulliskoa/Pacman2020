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
		coordinates[0] = 240;
	}
	if (coordinates[1] < -8) {
		coordinates[1] = 320;
	}

}

void MovingEntity::increaseSpeed()
{
	normalSpeed += 2;
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


