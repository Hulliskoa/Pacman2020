#pragma once
#include "InputComponent.h"
#include "Entity.h"

class AiComponent : public InputComponent
{
private:
	int targetTile[1][1] = {};
public:
	AiComponent();
	void update(int ghost, int* pacmanCoord, int* ghostCoord, EntityType currentEntityType);
	int* shadowAI(int* pacmanCoord, int* ghostCoord, EntityType currentEntityType);
	int* speedyAI(int* pacmanCoord, int* ghostCoord, EntityType currentEntityType);
	int* bashfulAI(int* pacmanCoord, int* ghostCoord, EntityType currentEntityType);
	int* pokeyAI(int* pacmanCoord, int* ghostCoord, EntityType currentEntityType);
};

