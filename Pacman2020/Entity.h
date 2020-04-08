#pragma once
#include "AnimationComponent.h"
#include "InputComponent.h"
#include "SDL.h"



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

private:
	int numFrames = 0;
	EntityType entityT = EntityType::NOT_DEFINED;
	SDL_Surface * spriteSheet;
	
public:
	//current direction the entity is travelling element 0 = x-plane and element 1 = y-plane.
	int velocity[2];
	//current coordinates to be used for rendering and collision checking
	int coordinates[2];
	
	std::shared_ptr<AnimationComponent> leftAnimation;
	std::shared_ptr<AnimationComponent>  rightAnimation;
	std::shared_ptr<AnimationComponent>  upAnimation;
	std::shared_ptr<AnimationComponent>  downAnimation;
	std::shared_ptr<AnimationComponent>  startAnimation;

	virtual void setVelocity(int x, int y);
	virtual void setCoordinates(int* newCoordinates);
	virtual void setEntityType(EntityType type);
	virtual EntityType getEntityType();
	virtual void update();

	Entity(SDL_Renderer* renderer ,int x, int y, int numAnimFrames, SDL_Surface * spriteSheet);
	Entity();

};

