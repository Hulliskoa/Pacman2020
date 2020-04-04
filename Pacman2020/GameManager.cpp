#include "GameManager.h"


GameManager::GameManager(SDL_Window* window, SDL_Renderer* renderer) :
	window(window),
	renderer(renderer),
	pacman(Pacman(renderer)),
	shadow(Shadow(renderer))
{
	collisionManager = CollisionManager();

	collisionManager.addEntity(shadow);

}




void GameManager::run()
{




	while (true) {
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);



		//entity update methods
		shadow.update();
		pacman.update(window);
		collisionManager.collisionCheck(pacman);

		SDL_RenderPresent(renderer);
		SDL_Delay(100);
	}



}
