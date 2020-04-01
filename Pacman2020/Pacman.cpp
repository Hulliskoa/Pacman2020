#include "Pacman.h"




void Pacman::update(SDL_Window* window)
{
	m_input.update(window, velocity);
}

Pacman::Pacman() {
	velocity[0] = {};
}


