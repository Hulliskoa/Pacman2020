#pragma once


#include <iostream>
#include "InputComponent.h"
#include "Renderer.h"
#include <SDL.h>

class Pacman
{
private:
	InputComponent m_input;
	int coordinates[2];
	int velocity[2];

public:
	void update(SDL_Window* window);
	Pacman();
	//Sprite mouthClosed;
	//Sprite midClose;
	//Sprite mouthOpen
};

