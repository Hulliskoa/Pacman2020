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

public:
	
	void update(SDL_Window* window) override;

	Pacman(SDL_Renderer* renderer);
	~Pacman();

};

