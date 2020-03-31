#pragma once


#include <iostream>
#include "InputComponent.h"
#include <SDL.h>

class Pacman
{
private:
	InputComponent m_input;

public:
	void update(SDL_Event event);
	Pacman();

};

