#include "AiComponent.h"

AiComponent::AiComponent() {
	lastVelocity = { 0,0 };
}
void AiComponent::setTarget(int x, int y)
{
	targetTile[x];
	targetTile[y];
	targetSet = true;
}
void AiComponent::removeTarget()
{
	targetSet = false;
}
void AiComponent::update(std::shared_ptr<Entity> currentGhost, int ghost, int* pacmanCoord, int* ghostCoord, std::shared_ptr<CollisionManager> collisionManager, int* velocity)
{
	switch (ghost)
	{
	case 0:
		shadowAI(currentGhost, pacmanCoord, ghostCoord, collisionManager, velocity);
		break;
	case 1:
		speedyAI(currentGhost, pacmanCoord, ghostCoord, collisionManager, velocity);
		break;
	case 2:
		bashfulAI(currentGhost, pacmanCoord, ghostCoord, collisionManager, velocity);
		break;
	case 3:
		pokeyAI(currentGhost, pacmanCoord, ghostCoord, collisionManager, velocity);
		break;
	default:
		break;
	}
}


void AiComponent::shadowAI(std::shared_ptr<Entity> currentGhost, int* pacmanCoord, int* ghostCoord, std::shared_ptr<CollisionManager> collisionManager, int* velocity)
{

	firstV.clear();
	secondV.clear();
	thirdV.clear();
	shortestPath.clear();

	lastVelocity[0] = velocity[0];
	lastVelocity[1] = velocity[1];

	if (!targetSet) {
		targetTile[0] = pacmanCoord[0];
		targetTile[1] = pacmanCoord[1];
	}


	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[0] = pow((currentGhost->coordinates[0] + velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + velocity[1]) - (targetTile[1]), 2);
		firstV.emplace_back(velocity[0]);
		firstV.emplace_back(velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[0], firstV));
	}

	velocity[0] = lastVelocity[1];
	velocity[1] = lastVelocity[0];

	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[1] = pow((currentGhost->coordinates[0] + velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + velocity[1]) - targetTile[1], 2);
		secondV.emplace_back(velocity[0]);
		secondV.emplace_back(velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[1], secondV));
	}

	velocity[0] = -lastVelocity[1];
	velocity[1] = -lastVelocity[0];

	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[2] = pow((currentGhost->coordinates[0] + velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + velocity[1]) - targetTile[1], 2);
		thirdV.emplace_back(velocity[0]);
		thirdV.emplace_back(velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[2], thirdV));
	}



	velocity[0] = shortestPath.begin()->second[0];
	velocity[1] = shortestPath.begin()->second[1];



}




void AiComponent::speedyAI(std::shared_ptr<Entity> currentGhost, int* pacmanCoord, int* ghostCoord, std::shared_ptr<CollisionManager> collisionManager, int* velocity)
{
	firstV.clear();
	secondV.clear();
	thirdV.clear();
	shortestPath.clear();

	lastVelocity[0] = velocity[0];
	lastVelocity[1] = velocity[1];

	if (velocity[0] > 0) {
		targetTile[0] = pacmanCoord[0] + 4;
	}
	else if (velocity[0] < 0) {
		targetTile[0] = pacmanCoord[0] - 4;
	}
	if (velocity[1] > 0) {
		targetTile[1] = pacmanCoord[1] + 4;
	}
	else if (velocity[1] < 0) {
		targetTile[1] = pacmanCoord[1] - 4;
	}



	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[0] = pow((currentGhost->coordinates[0] + velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + velocity[1]) - (targetTile[1]), 2);
		firstV.emplace_back(velocity[0]);
		firstV.emplace_back(velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[0], firstV));
	}

	velocity[0] = lastVelocity[1];
	velocity[1] = lastVelocity[0];


	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[1] = pow((currentGhost->coordinates[0] + velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + velocity[1]) - targetTile[1], 2);
		secondV.emplace_back(velocity[0]);
		secondV.emplace_back(velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[1], secondV));
	}

	velocity[0] = -lastVelocity[1];
	velocity[1] = -lastVelocity[0];

	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[2] = pow((currentGhost->coordinates[0] + velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + velocity[1]) - targetTile[1], 2);
		thirdV.emplace_back(velocity[0]);
		thirdV.emplace_back(velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[2], thirdV));
	}



	velocity[0] = shortestPath.begin()->second[0];
	velocity[1] = shortestPath.begin()->second[1];
}

void AiComponent::bashfulAI(std::shared_ptr<Entity> currentGhost, int* pacmanCoord, int* ghostCoord, std::shared_ptr<CollisionManager> collisionManager, int* velocity)
{
	firstV.clear();
	secondV.clear();
	thirdV.clear();
	shortestPath.clear();

	lastVelocity[0] = velocity[0];
	lastVelocity[1] = velocity[1];

	targetTile[0] = pacmanCoord[0];
	targetTile[1] = pacmanCoord[1];

	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[0] = pow((currentGhost->coordinates[0] + velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + velocity[1]) - (targetTile[1]), 2);
		firstV.emplace_back(velocity[0]);
		firstV.emplace_back(velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[0], firstV));
	}

	velocity[0] = lastVelocity[1];
	velocity[1] = lastVelocity[0];

	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[1] = pow((currentGhost->coordinates[0] + velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + velocity[1]) - targetTile[1], 2);
		secondV.emplace_back(velocity[0]);
		secondV.emplace_back(velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[1], secondV));
	}

	velocity[0] = -lastVelocity[1];
	velocity[1] = -lastVelocity[0];

	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[2] = pow((currentGhost->coordinates[0] + velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + velocity[1]) - targetTile[1], 2);
		thirdV.emplace_back(velocity[0]);
		thirdV.emplace_back(velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[2], thirdV));
	}



	velocity[0] = shortestPath.begin()->second[0];
	velocity[1] = shortestPath.begin()->second[1];
}

void AiComponent::pokeyAI(std::shared_ptr<Entity> currentGhost, int* pacmanCoord, int* ghostCoord, std::shared_ptr<CollisionManager> collisionManager, int* velocity)
{
	firstV.clear();
	secondV.clear();
	thirdV.clear();
	shortestPath.clear();

	lastVelocity[0] = velocity[0];
	lastVelocity[1] = velocity[1];

	targetTile[0] = pacmanCoord[0];
	targetTile[1] = pacmanCoord[1];

	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[0] = pow((currentGhost->coordinates[0] + velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + velocity[1]) - (targetTile[1]), 2);
		firstV.emplace_back(velocity[0]);
		firstV.emplace_back(velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[0], firstV));
	}

	velocity[0] = lastVelocity[1];
	velocity[1] = lastVelocity[0];

	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[1] = pow((currentGhost->coordinates[0] + velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + velocity[1]) - targetTile[1], 2);
		secondV.emplace_back(velocity[0]);
		secondV.emplace_back(velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[1], secondV));
	}

	velocity[0] = -lastVelocity[1];
	velocity[1] = -lastVelocity[0];

	if (collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::WALL && collisionManager->collisionCheck(currentGhost)->getEntityType() != EntityType::DOOR) {
		tilesChecked[2] = pow((currentGhost->coordinates[0] + velocity[0]) - (targetTile[0]), 2) + pow((currentGhost->coordinates[1] + velocity[1]) - targetTile[1], 2);
		thirdV.emplace_back(velocity[0]);
		thirdV.emplace_back(velocity[1]);
		shortestPath.insert(std::pair<int, std::vector<int>>(tilesChecked[2], thirdV));
	}



	velocity[0] = shortestPath.begin()->second[0];
	velocity[1] = shortestPath.begin()->second[1];
}
