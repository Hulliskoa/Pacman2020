#include "GameManager.h"


GameManager::GameManager(SDL_Window* window, SDL_Renderer* renderer) :
	window(window),
	gameRenderer(renderer)
{
	spriteSheet = IMG_Load("..\\Pacman2020\\sprites\\spritesheet.png");
	*gameState = GameState::GAME_STARTED;
	collisionManager = std::make_shared<CollisionManager>();
	levelManager = std::make_shared<LevelManager>(renderer);
	shadow = std::make_shared<Shadow>(gameRenderer, spriteSheet);
	pacman = std::make_shared<Pacman>(gameRenderer, window, spriteSheet);
	collisionManager->addEntity(shadow);
	collisionManager->addEntity(pacman);
	levelManager->createLevel(collisionManager, 1);

}

void GameManager::run()
{
	
	
	*gameState = GameState::GAME_RUNNING;
	while (*gameState == GameState::GAME_RUNNING) {
	

		SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(gameRenderer);
		//levelManager->renderLevel();
		//entity update methods
		shadow->update();
		pacman->update(gameState, collisionManager);


		/*
		while (*gameState == GameState::LEVEL_COMPLETE) {
			//reset dots
			//reset positions for all entities
			//increment to next level

		}
		*/

		/*
		while (*gameState == GameState::GAME_PAUSED) {
			//display menu
			//freeze everything else

		}
		*/


		SDL_RenderPresent(gameRenderer);
		SDL_Delay(100);
	}
	/*
	while (*gameState == GameState::EXIT_GAME) {

	}

	*/


}