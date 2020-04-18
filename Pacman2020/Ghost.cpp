#include "Ghost.h"
void Ghost::update(std::shared_ptr<GameState> gameState, SDL_Renderer* renderer, std::shared_ptr<MovingEntity> pacman, std::shared_ptr<CollisionManager> collisionManager)
{

	if (getEntityType() == EntityType::GHOST_EYES) {
		m_speed = m_normalSpeed;
		aiComponent->setTarget(112, 136);
		if (velocity[0] > 0) {
			returnRightAnimation->render(coordinates[0], coordinates[1], renderer, 0);
		}
		else if (velocity[0] < 0) {
			returnLeftAnimation->render(coordinates[0], coordinates[1], renderer, 0);
		}
		else if (velocity[1] > 0) {
			returnDownAnimation->render(coordinates[0], coordinates[1], renderer, 0);
		}
		else if (velocity[1] < 0) {
			returnUpAnimation->render(coordinates[0], coordinates[1], renderer, 0);
		}
		if (coordinates[0] == 112 && coordinates[1] == 136 && getEntityType() == EntityType::GHOST_EYES) {
			setEntityType(EntityType::GHOST_RETURN);
			aiComponent->setTarget(120, 120);
		}


	}
	else {
		m_speed = m_normalSpeed;
		if (*gameState == GameState::GAME_RUNNING || !outsideCage) {
			if (velocity[0] > 0) {
				rightAnimation->render(coordinates[0], coordinates[1], renderer, 0);
			}
			else if (velocity[0] < 0) {
				leftAnimation->render(coordinates[0], coordinates[1], renderer, 0);
			}
			else if (velocity[1] > 0) {
				downAnimation->render(coordinates[0], coordinates[1], renderer, 0);
			}
			else if (velocity[1] < 0) {
				upAnimation->render(coordinates[0], coordinates[1], renderer, 0);
			}
			else {
				startAnimation->render(coordinates[0], coordinates[1], renderer, 0);
			}
		}

		if (*gameState == GameState::GAME_RUNNING_FLEE && getEntityType() == EntityType::GHOST && outsideCage) {
			aiComponent->setTarget(pacman->coordinates[1], pacman->coordinates[0]);
			blueFleeAnimation->render(coordinates[0], coordinates[1], renderer, 0);
		}

		if (*gameState == GameState::GAME_RUNNING_FLEE_ENDING && getEntityType() == EntityType::GHOST && outsideCage) {
			aiComponent->setTarget(pacman->coordinates[1], pacman->coordinates[0]);
			if (alternateFleeAnimation) {
				blueFleeAnimation->render(coordinates[0], coordinates[1], renderer, 0);
				alternateFleeAnimation = false;
			}
			else {
				whiteFleeAnimation->render(coordinates[0], coordinates[1], renderer, 0);
				alternateFleeAnimation = true;
			}
		}
	}

	if (collisionManager->checkIntersection(shared_from_this())) {
		aiComponent->update(shared_from_this(), aiBehaviour, pacman, collisionManager, gameState);
	}

	coordinates[0] += (velocity[0] * m_speed);
	coordinates[1] += (velocity[1] * m_speed);

	//Resets target back to pacman after returned to cage
	if (coordinates[0] == 120 && coordinates[1] == 120 && getEntityType() == EntityType::GHOST_RETURN) {
		aiComponent->removeTarget();
		setOutSideCage(true);
		setEntityType(EntityType::GHOST);
	}

	MovingEntity::update();

}

Ghost::Ghost(SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth, int ai, int startingPositionX, int startingPositionY) : MovingEntity(startingPositionX, startingPositionY, 2, mainSpriteSheet, textureWidth, textureHeight) //aiBehaviour(ai)
{
	aiBehaviour = ai;
	setEntityType(EntityType::GHOST);
	aiComponent = std::make_shared<AiComponent>();
	setVelocity(1, 0);
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

