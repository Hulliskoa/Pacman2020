#include "Pacman.h"




void Pacman::update(SDL_Window* window)
{
	m_input.update(window, velocity);
	
	if (velocity[0] == 1) {
		rightAnimation.render(coordinates[0], coordinates[1]);

	}
	else if (velocity[0] == -1) {
		leftAnimation.render(coordinates[0], coordinates[1]);
	}
	else if (velocity[1] == 1)
	{
		upAnimation.render(coordinates[0], coordinates[1]);
	}
	else if (velocity[1] == -1)
	{
		downAnimation.render(coordinates[0], coordinates[1]);
	}
}

Pacman::Pacman() {
	velocity[0] = {};
}


