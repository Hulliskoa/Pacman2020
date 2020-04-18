#pragma once
#include "MovingEntity.h"
#include <SDL.h>
#include "CollisionManager.h"
#include "AiComponent.h"

/*! \brief
 *		Child class of MovingEntity and contains Ghost specific member variables and methods
 *
 *
 *	The different parts of the game is split in to different methods e.g mainMenu, inGame and so on.
 */

class Ghost :
	public MovingEntity
{
private:
	std::shared_ptr<AnimationComponent> blueFleeAnimation;/*!AnimationComponent for fleeing ghost*/
	std::shared_ptr<AnimationComponent> whiteFleeAnimation;/*!AnimationComponent for fleeing ghost*/
	std::shared_ptr<AnimationComponent> returnLeftAnimation;/*!AnimationComponent for ghost returning to cage after being eaten*/
	std::shared_ptr<AnimationComponent> returnRightAnimation;/*!AnimationComponent for ghost returning to cage after being eaten*/
	std::shared_ptr<AnimationComponent> returnUpAnimation;/*!AnimationComponent for ghost returning to cage after being eaten*/
	std::shared_ptr<AnimationComponent> returnDownAnimation;/*!AnimationComponent for ghost returning to cage after being eaten*/
	bool alternateFleeAnimation = true;/*!Boolean used for alternate between white and blue ghost animation at the end of the fleeing time*/
	int aiBehaviour;

public:
	
	std::shared_ptr<AiComponent> aiComponent;
	Ghost(SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth, int ai, int startingPositionX, int startingPositionY);
	/**
		Update function for handling all actions the ghost can make
		\param gameState global game state
		\param renderer global SDL_Renderer
		\param pacman pacman entity object
		\param collisionManager global collision manager
	*/
	void update(std::shared_ptr<GameState> gameState, SDL_Renderer* renderer, std::shared_ptr<MovingEntity> pacman, std::shared_ptr<CollisionManager> collisionManager);



};
