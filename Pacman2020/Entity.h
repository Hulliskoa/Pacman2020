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
	int velocity[2] = {0,0};
	int coordinates[2] = { 0,0 };
	//current coordinates to be used for rendering and collision checking
	std::shared_ptr<AnimationComponent>  startAnimation;
	Entity();
	Entity(SDL_Renderer* renderer, int x, int y, int numAnimFrames, SDL_Surface* mainSpriteSheet);
	void setCoordinates(int* newCoordinates);
	void setEntityType(EntityType type);
	EntityType getEntityType();
};

