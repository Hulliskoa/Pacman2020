#include "GameManager.h"


GameManager::GameManager(SDL_Window* window) : w(window)
{
	pacman = Pacman();

}

void GameManager::run()
{
	while (!quit) {
		
		pacman.update(w);
		
	}

}
