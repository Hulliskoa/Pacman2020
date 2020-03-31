#include "Pacman.h"


Pacman::Pacman()
{
	
}


void Pacman::update(SDL_Event event)
{
	m_input.update(event);
}

