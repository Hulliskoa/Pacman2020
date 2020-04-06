#pragma once
#include "AnimationComponent.h"
#include "InputComponent.h"
#include "SDL.h"


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
	int numFrames = 0;
	entityType entityT = NOT_DEFINED;
	SDL_Surface * spriteSheet;
public:
	int velocity[2];//current direction the entity is travelling element 0 = x plane and element 1 = y plane.
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
	virtual void update();
	virtual int* getNewLocation();

	Entity(SDL_Renderer* renderer ,int x, int y, int numAnimFrames, SDL_Surface * spriteSheet);
	Entity();

};

