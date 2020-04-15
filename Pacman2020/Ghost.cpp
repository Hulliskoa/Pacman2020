#include "Ghost.h"
void Ghost::update(SDL_Renderer* renderer, std::shared_ptr<MovingEntity> pacman, std::shared_ptr<CollisionManager> collisionManager)
{
	if (collisionManager->checkIntersection(shared_from_this())) {
		aiComponent->update(0, pacman->coordinates, coordinates, getEntityType());
		velocity[0] = 0;
		//std::shared_ptr<Entity> collidedwith = collisionManager->collisionCheck(shared_from_this());
	}

	

	coordinates[0] += velocity[0];
	coordinates[1] += velocity[1];

	rightAnimation->render(coordinates[0], coordinates[1], renderer);
	//midlertidig for å sjekke 
	/*
	if (animationCounter < 8) {
		rightAnimation->render(coordinates[0], coordinates[1], renderer);
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
	*/

	MovingEntity::update();
}

Ghost::Ghost(SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth) : MovingEntity(115, 120, 2, mainSpriteSheet, textureWidth, textureHeight)
{
	setEntityType(EntityType::GHOST);
	aiComponent = std::make_shared<AiComponent>();
	//Shadow
	rightAnimation->addRect(457, 65, 14, 14);
	rightAnimation->addRect(473, 65, 14, 14);

	setVelocity(1, 0);
	leftAnimation->addRect(489, 65, 14, 14);
	leftAnimation->addRect(505, 65, 14, 14);

	upAnimation->addRect(521, 65, 14, 14);
	upAnimation->addRect(537, 65, 14, 14);

	downAnimation->addRect(553, 65, 14, 14);
	downAnimation->addRect(569, 65, 14, 14);

	startAnimation->addRect(553, 65, 14, 14);
	startAnimation->addRect(553, 65, 14, 14);

}

