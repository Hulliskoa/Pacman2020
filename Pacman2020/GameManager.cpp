#include "GameManager.h"


GameManager::GameManager(SDL_Window* window) : 
	w(window), 
	pacman(Pacman()){}




void GameManager::run()
{
	while (true) {
		pacman.update(w);

	}

}
