#pragma once


#include <iostream>
#include <SDL.h>
#include "InputComponent.h"
#include "AnimationComponent.h"
#include "Entity.h"
#include "GameState.h"

class Pacman : public Entity
{
private:
	InputComponent m_input;
	SDL_Window * window;
public:
	
	void update(std::shared_ptr<GameState> gameState);
	Pacman(SDL_Renderer* renderer, SDL_Window * w, SDL_Surface * mainSpriteSheet);
	~Pacman();

};

