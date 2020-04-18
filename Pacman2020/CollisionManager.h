#pragma once
#include <vector>
#include "Entity.h"

/*! \brief
 *		Does collision checking on behalf of all the MovingEntity objects
 *
 *
 * The collision manager keeps track of all entities in game and can be called to check if an entity has collided with any of them. It is used inside all update methods of MovingEntity classes
 */
class CollisionManager
{
private:
	int hitBoxRadius = 8;/*!<Hitbox radius for the moving entity*/
	std::vector<std::shared_ptr<Entity>> entities;/*!<Vector containing all entities in the game*/

public:
	/**
		Checks if the entity has collided with anything and returns the pointer to the object it collided with
		\param entityToCheck the Entity that we want to check collision on
	*/
	std::shared_ptr<Entity>  collisionCheck(std::shared_ptr<Entity> entityToCheck);
	/**
		Used to add entities to the entities vector
		\param entity Entity we want to add to vector for collision checking later
	*/
	void addEntity(std::shared_ptr<Entity> entity);
	/**
		checks if entity is on top of an intersection
		\param entityToCheck Entity we want to check is on top of intersection
	*/
	bool checkIntersection(std::shared_ptr<Entity> entityToCheck);
	void clearEntityArray();
	CollisionManager();
	~CollisionManager();
};

