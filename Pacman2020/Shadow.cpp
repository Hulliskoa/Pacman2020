#include "Shadow.h"

void Shadow::update()
{

	//midlertidig for å sjekke collision
	if (animationCounter < 8) {
		rightAnimation->render(coordinates[0] += 8, coordinates[1]);
	}
	else if (animationCounter >= 8 && animationCounter < 16) {
		downAnimation->render(coordinates[0], coordinates[1] += 8);
	}
	else if (animationCounter >= 16 && animationCounter < 24) {
		leftAnimation->render(coordinates[0] -= 8, coordinates[1]);
	}
	else if (animationCounter >= 24) {
		upAnimation->render(coordinates[0], coordinates[1] -= 8);

	}
	animationCounter++;
	if (animationCounter == 32) {
		animationCounter = 0;
	}


	Entity::update();
}

Shadow::Shadow(SDL_Renderer* renderer, SDL_Surface* mainSpriteSheet) : Entity(renderer, 8, 8, 2, mainSpriteSheet)
{
	setEntityType(EntityType::GHOST);

	rightAnimation->addRect(457, 65, 14, 14);
	rightAnimation->addRect(473, 65, 14, 14);

	leftAnimation->addRect(489, 65, 14, 14);
	leftAnimation->addRect(505, 65, 14, 14);

	upAnimation->addRect(521, 65, 14, 14);
	upAnimation->addRect(537, 65, 14, 14);

	downAnimation->addRect(553, 65, 14, 14);
	downAnimation->addRect(569, 65, 14, 14);

}

Shadow::~Shadow()
{
}
