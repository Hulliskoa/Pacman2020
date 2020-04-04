#include "GameManager.h"


GameManager::GameManager(SDL_Window* window, SDL_Renderer* renderer) :
	window(window),
	gameRenderer(renderer)
{
	
	collisionManager = CollisionManager();
	shadow = std::make_shared<Shadow>(gameRenderer);
	pacman = std::make_shared<Pacman>(gameRenderer, window);
	collisionManager.addEntity(shadow);
	collisionManager.addEntity(pacman);
}





void GameManager::run()
{

	while (true) {
		SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(gameRenderer);

		//entity update methods
		shadow->update();
		pacman->update();
		collisionManager.collisionCheck(pacman);

		SDL_RenderPresent(gameRenderer);
		SDL_Delay(100);
	}



}
