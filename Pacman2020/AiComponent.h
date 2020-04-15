#pragma once
#include "InputComponent.h"
#include "Entity.h"
#include "CollisionManager.h"
#include <iostream> 
#include <iterator> 
#include <map> 
#include <algorithm>
#include <functional>

class AiComponent : public InputComponent
{
private:
	std::vector<double> tilesChecked = { 0,0,0 };
	int targetTile[2] = { 0,0 };
	std::vector<int> lastVelocity;
	std::vector <int> firstV;
	std::vector<int> secondV;
	std::vector<int> thirdV;
	bool targetSet = false;
	std::map<int, std::vector<int>> shortestPath;
	int speed = 4;
public:
	
	AiComponent();
	void setTarget(int x, int y);
	void update(std::shared_ptr<Entity> currentGhost, int ghost, int* pacmanCoord, int* ghostCoord, std::shared_ptr<CollisionManager> collisionManager, int * velocity);
	void shadowAI(std::shared_ptr<Entity> currentGhost, int* pacmanCoord, int* ghostCoord, std::shared_ptr<CollisionManager> collisionManager, int* velocity);
	void speedyAI(std::shared_ptr<Entity> currentGhost, int* pacmanCoord, int* ghostCoord, std::shared_ptr<CollisionManager> collisionManager, int* velocity);
	void bashfulAI(std::shared_ptr<Entity> currentGhost, int* pacmanCoord, int* ghostCoord, std::shared_ptr<CollisionManager> collisionManager, int* velocity);
	void pokeyAI(std::shared_ptr<Entity> currentGhost, int* pacmanCoord, int* ghostCoord, std::shared_ptr<CollisionManager> collisionManager, int* velocity);
	void removeTarget();
};

