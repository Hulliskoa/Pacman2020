#include "Ghost.h"
void Ghost::update(std::shared_ptr<GameState> gameState, SDL_Renderer* renderer, std::shared_ptr<MovingEntity> pacman, std::shared_ptr<CollisionManager> collisionManager)
{
	if (collisionManager->checkIntersection(shared_from_this())) {
		aiComponent->update(shared_from_this(),aiBehaviour, pacman, collisionManager);
		//std::shared_ptr<Entity> collidedwith = collisionManager->collisionCheck(shared_from_this());
	}



	coordinates[0] += velocity[0];
	coordinates[1] += velocity[1];
	if (*gameState == GameState::GAME_RUNNING) {
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
	}

	if (*gameState == GameState::GAME_RUNNING_FLEE) {
		aiComponent->setTarget(rand() % 400 + 1, rand() % 400 + 1);
		blueFleeAnimation->render(coordinates[0], coordinates[1], renderer);
	}

	if (*gameState == GameState::GAME_RUNNING_FLEE_ENDING) {
		aiComponent->setTarget(rand() % 400 + 1, rand() % 400 + 1);
		if (alternateFleeAnimation) {
			blueFleeAnimation->render(coordinates[0], coordinates[1], renderer);
			alternateFleeAnimation = false;
		}
		else { 
			whiteFleeAnimation->render(coordinates[0], coordinates[1], renderer);
			alternateFleeAnimation = true;
		}
	
	}


	MovingEntity::update();

}

Ghost::Ghost(SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth, int ai, int startingPositionX, int startingPositionY) : MovingEntity(startingPositionX, startingPositionY, 2, mainSpriteSheet, textureWidth, textureHeight), aiBehaviour(ai)
{
	setEntityType(EntityType::GHOST);
	aiComponent = std::make_shared<AiComponent>();

	blueFleeAnimation = std::make_shared<AnimationComponent>(2, mainSpriteSheet, textureWidth, textureHeight);
	blueFleeAnimation->addRect(585, 65, 14, 14);
	blueFleeAnimation->addRect(601, 65, 14, 14);

	whiteFleeAnimation = std::make_shared<AnimationComponent>(2, mainSpriteSheet, textureWidth, textureHeight);
	whiteFleeAnimation->addRect(617, 65, 14, 14);
	whiteFleeAnimation->addRect(633, 65, 14, 14);

	returnLeftAnimation = std::make_shared<AnimationComponent>(1, mainSpriteSheet, textureWidth, textureHeight);
	returnRightAnimation = std::make_shared<AnimationComponent>(1, mainSpriteSheet, textureWidth, textureHeight);
	returnUpAnimation = std::make_shared<AnimationComponent>(1, mainSpriteSheet, textureWidth, textureHeight);
	returnDownAnimation = std::make_shared<AnimationComponent>(1, mainSpriteSheet, textureWidth, textureHeight);

	returnLeftAnimation->addRect(601, 81, 14, 14);
	returnRightAnimation->addRect(585, 81, 14, 14);
	returnUpAnimation->addRect(617, 81, 14, 14);
	returnDownAnimation->addRect(633, 81, 14, 14);





}

