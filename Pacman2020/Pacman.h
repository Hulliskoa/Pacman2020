#pragma once


#include <iostream>
#include "InputComponent.h"
#include "Renderer.h"
#include <SDL.h>

class Pacman
{
private:
	InputComponent m_input;
	Renderer m_render;
	int velocity[2];

public:
	void update(SDL_Window* window);
	Pacman();

};

