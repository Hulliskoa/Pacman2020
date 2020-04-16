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
	int velocity[2];//current direction pacman is travelling element 0 = x plane and element 1 = y plane.

public:
	int coordinates[2];//current coordinates to be used in rendering
	AnimationComponent leftAnimation;
	AnimationComponent rightAnimation;
	AnimationComponent upAnimation;
	AnimationComponent downAnimation;
	AnimationComponent startAnimation;
	void update(SDL_Window* window) override;

	Pacman(SDL_Renderer* renderer);
	~Pacman();

};

