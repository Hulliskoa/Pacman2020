#include "GameManager.h"


GameManager::GameManager(SDL_Window* window, SDL_Renderer* renderer) :

	window(window),
	renderer(renderer),
	pacman(Pacman(renderer)) {
}




void GameManager::run()
{
	while (true) {
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		
		pacman.update(window);

		SDL_RenderPresent(renderer);
		SDL_Delay(200);
	}

}
