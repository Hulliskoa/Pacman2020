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
void AiComponent::update(std::shared_ptr<Entity> currentGhost, int ghostAI, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager)
{
	switch (ghostAI)
	{
	case 0:
		shadowAI(currentGhost, pacman, collisionManager);
		break;
	case 1:
		speedyAI(currentGhost, pacman, collisionManager);
		break;
	case 2:
		bashfulAI(currentGhost, pacman, collisionManager);
		break;
	case 3:
		pokeyAI(currentGhost, pacman, collisionManager);
		break;
	default:
		break;
	}
}


void AiComponent::shadowAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager)
{
	if (!targetSet) {
		targetTile[0] = pacman->coordinates[0];
		targetTile[1] = pacman->coordinates[1];
	}
	ai(currentGhost, pacman, collisionManager);
}




void AiComponent::speedyAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager)
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

	ai(currentGhost, pacman, collisionManager);
}

void AiComponent::bashfulAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager)
{
	if (!targetSet) {
		targetTile[0] = pacman->coordinates[0];
		targetTile[1] = pacman->coordinates[1];
	}
	ai(currentGhost, pacman, collisionManager);
}

void AiComponent::pokeyAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager)
{
	if (!targetSet) {
		targetTile[0] = pacman->coordinates[0];
		targetTile[1] = pacman->coordinates[1];
	}

	ai(currentGhost, pacman, collisionManager);
}

void AiComponent::ai(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager)
{
	firstV.clear();
	secondV.clear();
	thirdV.clear();
	shortestPath.clear();

	lastVelocity[0] = currentGhost->velocity[0];
	lastVelocity[1] = currentGhost->velocity[1];

	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[0] = pow((currentGhost->coordinates[0] + currentGhost->velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + currentGhost->velocity[1]) - (targetTile[1]), 2);
		firstV.emplace_back(currentGhost->velocity[0]);
		firstV.emplace_back(currentGhost->velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[0], firstV));
	}

	currentGhost->velocity[0] = lastVelocity[1];
	currentGhost->velocity[1] = lastVelocity[0];


	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[1] = pow((currentGhost->coordinates[0] + currentGhost->velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + currentGhost->velocity[1]) - targetTile[1], 2);
		secondV.emplace_back(currentGhost->velocity[0]);
		secondV.emplace_back(currentGhost->velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[1], secondV));
	}

	currentGhost->velocity[0] = -lastVelocity[1];
	currentGhost->velocity[1] = -lastVelocity[0];

	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[2] = pow((currentGhost->coordinates[0] + currentGhost->velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + currentGhost->velocity[1]) - targetTile[1], 2);
		thirdV.emplace_back(currentGhost->velocity[0]);
		thirdV.emplace_back(currentGhost->velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[2], thirdV));
	}


	currentGhost->velocity[0] = shortestPath.begin()->second[0];
	currentGhost->velocity[1] = shortestPath.begin()->second[1];
}
