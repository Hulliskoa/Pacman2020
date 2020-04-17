#pragma once
#include "InputComponent.h"
#include "CollisionManager.h"
#include "Entity.h"
#include <iostream> 
#include <iterator> 
#include <map> 
#include <algorithm>
#include <functional>

class AiComponent : public InputComponent
{
private:
	std::vector<double> tilesChecked = { 0,0,0 };
	std::vector<int> targetTile;
	std::vector<int> lastVelocity;
	std::vector <int> firstV;
	std::vector<int> secondV;
	std::vector<int> thirdV;
	bool targetSet = false;
	std::map<int, std::vector<int>> shortestPath;

	bool eaten = false;

public:
	AiComponent();
	void setTarget(int x, int y);
	void update(std::shared_ptr<Entity> currentGhost, int ghostAi, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState);
	void shadowAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState);
	void speedyAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManage, std::shared_ptr<GameState> gameState);
	void bashfulAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState);
	void pokeyAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState);
	void ai(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState);
	bool checkIfReturn(std::shared_ptr<Entity> currentGhost, std::shared_ptr<CollisionManager> collisionManager);
	void removeTarget();
};

