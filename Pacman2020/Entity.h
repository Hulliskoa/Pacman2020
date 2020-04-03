#pragma once
#include "AnimationComponent.h"
#include "InputComponent.h"


enum entityType {
	PACMAN,
	GHOST,
	AFRAID_GHOST,
	PELLET,
	POWER_PELLET,
	FRUIT,
	WALL,
	TELEPORT,
	NOT_DEFINED
};

class Entity
{

private:
	InputComponent m_input;
	int velocity[2];//current direction pacman is travelling element 0 = x plane and element 1 = y plane.
	entityType entityT = NOT_DEFINED;
public:

	int coordinates[2];//current coordinates to be used in rendering and collision
	AnimationComponent leftAnimation;
	AnimationComponent rightAnimation;
	AnimationComponent upAnimation;
	AnimationComponent downAnimation;
	AnimationComponent startAnimation;

	virtual void setVelocity(int x, int y);
	virtual void setCoordinates(int* newCoordinates);
	virtual void setEntityType(entityType type);
	virtual entityType getEntityType();
	virtual void update(SDL_Window* window);
	virtual int* getNewLocation();


};

