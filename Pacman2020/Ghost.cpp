#include "Ghost.h"
void Ghost::update(SDL_Renderer* renderer)
{

	//midlertidig for å sjekke collision
	if (animationCounter < 8) {
		rightAnimation->render(coordinates[0] += 8, coordinates[1], renderer);
	}
	else if (animationCounter >= 8 && animationCounter < 16) {
		downAnimation->render(coordinates[0], coordinates[1] += 8, renderer);
	}
	else if (animationCounter >= 16 && animationCounter < 24) {
		leftAnimation->render(coordinates[0] -= 8, coordinates[1], renderer);
	}
	else if (animationCounter >= 24) {
		upAnimation->render(coordinates[0], coordinates[1] -= 8, renderer);

	}
	animationCounter++;
	if (animationCounter == 32) {
		animationCounter = 0;
	}


	MovingEntity::update();
}

Ghost::Ghost(SDL_Window* w, SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth) : MovingEntity(32, 40, 3, mainSpriteSheet, textureWidth, textureHeight)
{
	setEntityType(EntityType::GHOST);

	//Shadow
	rightAnimation->addRect(457, 65, 14, 14);
	rightAnimation->addRect(473, 65, 14, 14);

	leftAnimation->addRect(489, 65, 14, 14);
	leftAnimation->addRect(505, 65, 14, 14);

	upAnimation->addRect(521, 65, 14, 14);
	upAnimation->addRect(537, 65, 14, 14);

	downAnimation->addRect(553, 65, 14, 14);
	downAnimation->addRect(569, 65, 14, 14);

}

