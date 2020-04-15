#include "Ghost.h"
void Ghost::update(SDL_Renderer* renderer, std::shared_ptr<MovingEntity> pacman, std::shared_ptr<CollisionManager> collisionManager)
{
	if (collisionManager->checkIntersection(shared_from_this())) {
		aiComponent->update(shared_from_this(), 0, pacman->coordinates, coordinates, collisionManager, velocity);
		//std::shared_ptr<Entity> collidedwith = collisionManager->collisionCheck(shared_from_this());
	}



	coordinates[0] += velocity[0];
	coordinates[1] += velocity[1];

	if (velocity[0] > 0) {

		rightAnimation->render(coordinates[0], coordinates[1], renderer);

	}
	else if (velocity[0] < 0) {

		leftAnimation->render(coordinates[0], coordinates[1], renderer);

	}

	else if (velocity[1] > 0) {

		downAnimation->render(coordinates[0], coordinates[1], renderer);

	}
	else if (velocity[1] < 0) {

		upAnimation->render(coordinates[0], coordinates[1], renderer);

	}
	else {

		startAnimation->render(coordinates[0], coordinates[1], renderer);
	}

	MovingEntity::update();

}

Ghost::Ghost(SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth, int ai, int startingPositionX, int startingPositionY) : MovingEntity(startingPositionX, startingPositionY, 2, mainSpriteSheet, textureWidth, textureHeight), aiBehaviour(ai)
{
	setEntityType(EntityType::GHOST);
	aiComponent = std::make_shared<AiComponent>();


}

