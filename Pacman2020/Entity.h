#pragma once

#include "AnimationComponent.h"
#include "InputComponent.h"
#include <SDL.h>

/**
	Enum class for keeping track of what kind of entity the object is.
*/
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

/*! \brief
 *		All ingame objects are either an Entity or derived from it - see: MovingEntity, Pacman, Shadow
 *
 *
 *  The whole game is built up by entities. These have different entity types that define their behaviour when pacman collide with them
 */
class Entity
{
protected:
	EntityType entityT = EntityType::NOT_DEFINED;/*!<Defines what entity type the object is*/
	int numFrames = 0;

public:
	int velocity[2] = { 0,0 };/*!<current direction the entity is travelling. element 0 = x-plane and element 1 = y-plane.*/
	int coordinates[2] = { 0,0 };/*!<current coordinates to be used for rendering and collision checking. element 0 = x-coordinate and element 1 = y-coordinate.*/
	std::shared_ptr<AnimationComponent>  startAnimation;/*!<Animation used at the start of game or if the object is stationary*/

	Entity();
	Entity(int xStart, int yStart, int numAnimFrames, SDL_Texture* spriteTexture, int spriteWidth, int spriteHeight);
	void setCoordinates(int* newCoordinates);
	void setEntityType(EntityType type);
	EntityType getEntityType();
};

