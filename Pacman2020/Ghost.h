#pragma once
#include "MovingEntity.h"
#include <SDL.h>
#include "AiComponent.h"
#include "CollisionManager.h"


class Ghost :
	public MovingEntity
{
private:

	int animationCounter = 0;
	std::shared_ptr<Entity> pacman;
	int aiBehaviour;
public:
	std::shared_ptr<AiComponent> aiComponent;
	void update(SDL_Renderer* renderer, std::shared_ptr<MovingEntity> pacman, std::shared_ptr<CollisionManager> collisionManager);
	Ghost(SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth, int ai, int startingPositionX, int startingPositionY);

};
