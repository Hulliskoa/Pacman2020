#pragma once
#include "MovingEntity.h"
#include <SDL.h>
#include "CollisionManager.h"
#include "AiComponent.h"

class Ghost :
	public MovingEntity
{
private:
	
	int animationCounter = 0;
	std::shared_ptr<AnimationComponent> blueFleeAnimation;
	std::shared_ptr<AnimationComponent> whiteFleeAnimation;
	std::shared_ptr<AnimationComponent> returnLeftAnimation;
	std::shared_ptr<AnimationComponent> returnRightAnimation;
	std::shared_ptr<AnimationComponent> returnUpAnimation;
	std::shared_ptr<AnimationComponent> returnDownAnimation;
	bool alternateFleeAnimation = true;
	std::shared_ptr<Entity> pacman;
	int aiBehaviour;

public:
	std::shared_ptr<AiComponent> aiComponent;
	void update(std::shared_ptr<GameState> gameState, SDL_Renderer* renderer, std::shared_ptr<MovingEntity> pacman, std::shared_ptr<CollisionManager> collisionManager);
	Ghost(SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth, int ai, int startingPositionX, int startingPositionY);


};
