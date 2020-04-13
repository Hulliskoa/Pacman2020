#pragma once


#include <iostream>
#include <SDL.h>
#include "InputComponent.h"
#include "AnimationComponent.h"
#include "MovingEntity.h"
#include "GameState.h"
#include "CollisionManager.h"

class Pacman : public MovingEntity
{
private:
	InputComponent m_input;
	SDL_Window* window;
	AnimationComponent deathAnimation;
	std::shared_ptr<AnimationComponent> lastAnimation = nullptr;
public:

	void update(std::shared_ptr<GameState> gameState, std::shared_ptr<CollisionManager> collisionManager, SDL_Renderer * renderer);
	Pacman(SDL_Window* w, SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth);
	~Pacman();

};

