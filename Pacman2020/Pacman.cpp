#include "Pacman.h"




void Pacman::update()
{
	m_input.update(window, velocity);
}

Pacman::Pacman(SDL_Window* w) : window(w) {
	velocity[0] = {};
}


