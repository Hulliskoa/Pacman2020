#pragma once

#include "Entity.h"




/**
	MovingEntity class is derived from Entity super class and is used to create all moving entities in the game.
*/
class MovingEntity : public Entity, public std::enable_shared_from_this<MovingEntity>
{
protected:

	int normalSpeed = 2;
	int speed = normalSpeed;
	int halfSpeed = normalSpeed / 2;
	int doubleSpeed = normalSpeed * 2;
public:
	std::shared_ptr<AnimationComponent> leftAnimation;/*!<Animation used for animating movement towards the left*/
	std::shared_ptr<AnimationComponent>  rightAnimation;/*!<Animation used for animating movement towards the right*/
	std::shared_ptr<AnimationComponent>  upAnimation; /*!<Animation used for animating movement upwards*/
	std::shared_ptr<AnimationComponent>  downAnimation;/*!<Animation used for animating movement downwards*/

	MovingEntity(int xStart, int yStart, int numAnimFrames, SDL_Texture* mainSpriteSheet, int textureWidth, int textureHeight);
	MovingEntity();

	virtual void setVelocity(int x, int y);
	virtual void update();
	void increaseSpeed();
	void setBaseSpeed(int speed);
	int getSpeed();

};

