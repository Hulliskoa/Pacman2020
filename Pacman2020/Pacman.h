#pragma once


#include <iostream>
#include <SDL.h>
#include "InputComponent.h"
#include "Animation.h"

class Pacman
{
private:
	InputComponent m_input;
	int coordinates[2];//current coordinates to be used in rendering
	int velocity[2];//current direction pacman is travelling element 0 = x plane and element 1 = y plane.

public:
	AnimationComponent leftAnimation;
	AnimationComponent rightAnimation;
	AnimationComponent upAnimation;
	AnimationComponent downAnimation;

	void update(SDL_Window* window);

	Pacman(SDL_Renderer* renderer);
	~Pacman();

};

