#pragma once

#include "AnimationComponent.h"
#include <SDL.h>


/**
	Enum class for keeping track of what kind of entity the object is.
*/
enum class EntityType {
	PACMAN,
	GHOST,
	GHOST_EYES,
	GHOST_RETURN,
	PELLET,
	POWER_PELLET,
	INACTIVE_PELLET,
	INACTIVE_POWER_PELLET,
	FRUIT,
	INACTIVE_FRUIT,
	WALL,
	INTERSECTION,
	DOOR,
	NOT_DEFINED
};

/*! \brief
 *		All ingame objects are either an Entity or derived from it - see: MovingEntity
 *
 *
 *  The whole game is built up by entities. These have different entity types that define their behaviour when pacman collide with them
 */
class Entity
{
protected:
	EntityType entityT = EntityType::NOT_DEFINED;/*!<Defines what entity type the object is*/
	int numFrames = 0;
	bool outsideCage = false;
public:

	std::vector<int> velocity = { 0,0 };/*!<current direction the entity is travelling. element 0 = x-plane and element 1 = y-plane.*/
	int coordinates[2] = { 0,0 };/*!<current coordinates to be used for rendering and collision checking. element 0 = x-coordinate and element 1 = y-coordinate.*/
	std::shared_ptr<AnimationComponent>  startAnimation;/*!<Animation used at the start of game or if the object is stationary*/

	Entity();
	/**Constructor
		\param xStart x coordinate for starting position
		\param yStart y coordinate for starting position
		\param numAnimFrames number of frames in the entityes animations
		\param spriteTexture sprite texture for rendering sprites
		\param spriteWidth width of sprite texture in pixels
		\param spriteHeight heigth of sprite texture in pixels
	*/
	Entity(int xStart, int yStart, int numAnimFrames, SDL_Texture* spriteTexture, int spriteWidth, int spriteHeight);

	/**Manually sets new coordinates for the entity
		\param x x coordinate
		\param y y coordinate
	*/
	void setCoordinates(int x, int y);

	/**Sets the entityT member variable
		\param type the EntityType that entityT is going to be set to.
	*/
	void setEntityType(EntityType type);

	/**Returns the entityT member variable
	*/
	EntityType getEntityType();

	void setOutSideCage(bool isOutSide);
};

