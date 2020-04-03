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
		//renders maze
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		for (int i = 0; i < 31; i++) {
			for (int z = 0; z < 28; z++) {
				if (mapTest[i][z] == 1) {
					for (int x = 0; x < 13; x++) {
						for (int y = 0; y < 13; y++) {
							SDL_RenderDrawPoint(renderer, currentpos[0] + y, currentpos[1] + x);
						}
					}

				}
				 
				currentpos[0] += 13;
			}
			currentpos[0] = 0;
			currentpos[1] += 13;
		
		}
		currentpos[0] = 0;
		currentpos[1] = 0;


		//entity update methods
		
		pacman.update(window);
		/*
			map.update();
			ghost.update();
		*/
	


		SDL_RenderPresent(renderer);
		SDL_Delay(100);
	}



}
