#pragma once

#include "AnimationComponent.h"
#include "InputComponent.h"
#include <SDL.h>

enum class EntityType {
	PACMAN,
	GHOST,
	AFRAID_GHOST,
	PELLET,
	POWER_PELLET,
	INACTIVE_PELLET,
	FRUIT,
	WALL,
	TELEPORT,
	NOT_DEFINED
};


class Entity
{
protected:
	EntityType entityT = EntityType::NOT_DEFINED;
	
	//SDL_Surface* spriteSheet;
public:
	int coordinates[2];
	//current coordinates to be used for rendering and collision checking

	Entity();
	virtual void setCoordinates(int* newCoordinates);
	virtual void setEntityType(EntityType type);
	virtual EntityType getEntityType();
};

