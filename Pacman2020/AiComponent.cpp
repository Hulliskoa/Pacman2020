#include "AiComponent.h"

AiComponent::AiComponent() {
	lastVelocity = { 0,0 };
	targetTile = { 0,0 };
	targetTile[0] = 0;
	targetTile[1] = 0;
}
void AiComponent::setTarget(int x, int y)
{
	targetTile[0] = x;
	targetTile[1] = y;
	targetSet = true;
}
void AiComponent::removeTarget()
{
	targetSet = false;
}
void AiComponent::update(std::shared_ptr<Entity> currentGhost, int ghostAI, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState)
{
	switch (ghostAI)
	{
	case 0:
		shadowAI(currentGhost, pacman, collisionManager, gameState);
		break;
	case 1:
		speedyAI(currentGhost, pacman, collisionManager, gameState);
		break;
	case 2:
		bashfulAI(currentGhost, pacman, collisionManager, gameState);
		break;
	case 3:
		pokeyAI(currentGhost, pacman, collisionManager, gameState);
		break;
	default:
		break;
	}
}


void AiComponent::shadowAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState)
{
	if (!targetSet) {
		targetTile[0] = pacman->coordinates[0];
		targetTile[1] = pacman->coordinates[1];
	}
	ai(currentGhost, pacman, collisionManager, gameState);
}




void AiComponent::speedyAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState)
{
	if (!targetSet) {
		targetTile[0] = pacman->coordinates[0];
		targetTile[1] = pacman->coordinates[1];

		if (pacman->velocity[0] > 0) {
			targetTile[0] += 4;
		}
		else if (pacman->velocity[0] < 0) {
			targetTile[0] -= 4;
		}
		if (pacman->velocity[1] > 0) {
			targetTile[1] += 4;
		}
		else if (pacman->velocity[1] < 0) {
			targetTile[1] -= 4;
		}

	}

	ai(currentGhost, pacman, collisionManager, gameState);
}

void AiComponent::bashfulAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState)
{
	if (!targetSet) {
		targetTile[0] = pacman->coordinates[0];
		targetTile[1] = pacman->coordinates[1];
	}
	ai(currentGhost, pacman, collisionManager, gameState);
}

void AiComponent::pokeyAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState)
{
	if (!targetSet) {
		targetTile[0] = pacman->coordinates[0];
		targetTile[1] = pacman->coordinates[1];
	}

	ai(currentGhost, pacman, collisionManager, gameState);
}

void AiComponent::ai(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState)
{
	firstV.clear();
	secondV.clear();
	thirdV.clear();
	shortestPath.clear();

	lastVelocity[0] = currentGhost->velocity[0];
	lastVelocity[1] = currentGhost->velocity[1];

	//checks if collision is with pacman
	std::shared_ptr<Entity> collidedWith = collisionManager->collisionCheckMoving(currentGhost);
	if (collidedWith != nullptr) {
		if (collidedWith->getEntityType() == EntityType::PACMAN && currentGhost->getEntityType() != EntityType::GHOST_EYES) {
			if (*gameState == GameState::GAME_RUNNING_FLEE || *gameState == GameState::GAME_RUNNING_FLEE_ENDING) {
				currentGhost->setEntityType(EntityType::GHOST_EYES);
			}
			else if (*gameState == GameState::GAME_RUNNING) {
				*gameState = GameState::PACMAN_DIED;
			}
		}
	}
	else {


		//Checks tile directly in front of ghost
		if (collisionManager->collisionCheckStationary(currentGhost)->getEntityType() != EntityType::WALL && checkIfReturn(currentGhost, collisionManager)) {
			tilesChecked[0] = pow((currentGhost->coordinates[0] + currentGhost->velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + currentGhost->velocity[1]) - (targetTile[1]), 2);
			firstV.emplace_back(currentGhost->velocity[0]);
			firstV.emplace_back(currentGhost->velocity[1]);
			shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[0], firstV));
		}

		//check next tile in left direction
		currentGhost->velocity[0] = lastVelocity[1];
		currentGhost->velocity[1] = lastVelocity[0];

		if (collisionManager->collisionCheckStationary(currentGhost)->getEntityType() != EntityType::WALL && checkIfReturn(currentGhost, collisionManager)) {
			tilesChecked[1] = pow((currentGhost->coordinates[0] + currentGhost->velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + currentGhost->velocity[1]) - targetTile[1], 2);
			secondV.emplace_back(currentGhost->velocity[0]);
			secondV.emplace_back(currentGhost->velocity[1]);
			shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[1], secondV));
		}

		//check next tile in right direction
		currentGhost->velocity[0] = -lastVelocity[1];
		currentGhost->velocity[1] = -lastVelocity[0];

		if (collisionManager->collisionCheckStationary(currentGhost)->getEntityType() != EntityType::WALL && checkIfReturn(currentGhost, collisionManager)) {
			tilesChecked[2] = pow((currentGhost->coordinates[0] + currentGhost->velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + currentGhost->velocity[1]) - targetTile[1], 2);
			thirdV.emplace_back(currentGhost->velocity[0]);
			thirdV.emplace_back(currentGhost->velocity[1]);
			shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[2], thirdV));
		}

		//fetch shortest path from map
		currentGhost->velocity[0] = shortestPath.begin()->second[0];
		currentGhost->velocity[1] = shortestPath.begin()->second[1];
	}

}

bool AiComponent::checkIfReturn(std::shared_ptr<Entity> currentGhost, std::shared_ptr<CollisionManager> collisionManager)
{
	for (auto collidedWith : collisionManager->collisionCheck(currentGhost)) {
		if (currentGhost->getEntityType() == EntityType::GHOST_EYES || currentGhost->getEntityType() == EntityType::GHOST_RETURN && collidedWith->getEntityType() == EntityType::DOOR) {
			return true;
		}
		else if (collidedWith->getEntityType() != EntityType::DOOR) {
			return true;
		}
		else if (collidedWith->getEntityType() == EntityType::DOOR) {
			return false;
		}
	}

}
