#pragma once


#include <iostream>
#include <SDL.h>
#include "InputComponent.h"
#include "AnimationComponent.h"
#include "Entity.h"

class Pacman : public Entity
{
private:
	InputComponent m_input;
	SDL_Window * window;
public:
	
	void update();
	Pacman(SDL_Renderer* renderer, SDL_Window * w);
	~Pacman();

};

