#pragma once


#include <iostream>
#include <SDL.h>
#include "InputComponent.h"
#include "AnimationComponent.h"
#include "Entity.h"
#include "GameState.h"
#include "CollisionManager.h"

class Pacman : public Entity
{
private:
	InputComponent m_input;
	SDL_Window * window;
	AnimationComponent deathAnimation;
	std::shared_ptr<AnimationComponent> lastAnimation = nullptr;
public:
	
	void update(std::shared_ptr<GameState> gameState, std::shared_ptr<CollisionManager> collisionManager);
	Pacman(SDL_Renderer* renderer, SDL_Window * w, SDL_Surface * mainSpriteSheet);
	~Pacman();

};

