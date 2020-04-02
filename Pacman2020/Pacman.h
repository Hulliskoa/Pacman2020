#pragma once


#include <iostream>
#include "InputComponent.h"
#include <SDL.h>
#include "Animation.h"

class Pacman
{
private:
	InputComponent m_input;
	int coordinates[2];
	int velocity[2];

public:
	Animation leftAnimation;
	Animation rightAnimation;
	Animation upAnimation;
	Animation downAnimation;
	void update(SDL_Window* window);
	Pacman(SDL_Renderer* renderer);

};

