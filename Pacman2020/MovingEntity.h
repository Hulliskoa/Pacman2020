#pragma once

#include "Entity.h"





/*! \brief
 *		MovingEntity class is derived from Entity super class and is used to create all moving entities in the game.
 *

 */
class MovingEntity : public Entity, public std::enable_shared_from_this<MovingEntity>
{
protected:
	int m_normalSpeed = 2;/*!<Normal speed for an moving entity*/
	int m_speed = m_normalSpeed;/*!<speed is the same as normal speed on creation*/
	int m_halfSpeed = m_normalSpeed / 2;/*!<normalSpeed / 2*/
	int m_doubleSpeed = m_normalSpeed * 2;/*!<normalSpeed * 2*/
public:
	std::shared_ptr<AnimationComponent> leftAnimation;/*!<Animation used for animating movement towards the left*/
	std::shared_ptr<AnimationComponent>  rightAnimation;/*!<Animation used for animating movement towards the right*/
	std::shared_ptr<AnimationComponent>  upAnimation; /*!<Animation used for animating movement upwards*/
	std::shared_ptr<AnimationComponent>  downAnimation;/*!<Animation used for animating movement downwards*/

	/**
		Constructor
		\param xStart starting x-coordinate
		\param yStart starting y-coordinate
		\param numAnimFrames number of frames to be used in animations
		\param  mainSpriteSheet spritesheet texture loaded in game manager
		\param  textureWidth height of spritesheetsTexture
		\param  textureHeight widht of spritesheetsTexture
	*/
	MovingEntity(int xStart, int yStart, int numAnimFrames, SDL_Texture* mainSpriteSheet, int textureWidth, int textureHeight);
	MovingEntity();

	/**
		Used to read .txt file and convert it into the levelArray
		\param x value for direction in the x plane
		\param y value for direction in the y plane
	*/
	virtual void setVelocity(int x, int y);

	/**
		Virtual update method for use implementation in child classes
	*/
	virtual void update();
	/**
		Increses speed by 2;
	*/
	void increaseSpeed();

	/**
		sets base speed;
	*/
	void setBaseSpeed(int speed);
	/**
		returns current speed
	*/
	int getSpeed();

};

