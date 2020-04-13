#pragma once
#include <vector>
#include "Entity.h"
#include "MovingEntity.h"

/*! \brief
 *		Does collision checking on behalf of all the MovingEntity objects
 *
 *
 * The collision manager keeps track of all entities in game and can be called to check if an entity has collided with any of them
 */
class CollisionManager
{
private:
	int hitBoxRadius = 8;/*!<Hitbox radious for the moving entity*/
	std::vector<std::shared_ptr<Entity>> entities;/*!<Vector containing all entities in the game*/

public:
	/**
		Checks if the entity has collided with anything and returns the pointer to the object it collided with
		\param entityToCheck the Entity that we want to check collision on
	*/
	std::shared_ptr<Entity>  collisionCheck(Entity* entityToCheck);
	/**
		Used to add entities to the entities vector
		\param entity Entity we want to add to vector for collision checking later
	*/
	void addEntity(std::shared_ptr<Entity> entity);
	void clearEntityArray();
	CollisionManager();
	~CollisionManager();
};

