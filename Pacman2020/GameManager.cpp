#include "GameManager.h"


GameManager::GameManager(SDL_Window* window, SDL_Renderer* renderer) :
	window(window),
	gameRenderer(renderer)
{
	spriteSheet = IMG_Load("..\\Pacman2020\\sprites\\spritesheet.png");
	*gameState = GameState::GAME_STARTED;
	collisionManager = CollisionManager();

	shadow = std::make_shared<Shadow>(gameRenderer, spriteSheet);
	pacman = std::make_shared<Pacman>(gameRenderer, window, spriteSheet);
	collisionManager.addEntity(shadow);
	collisionManager.addEntity(pacman);
}

void GameManager::run()
{

	*gameState = GameState::GAME_RUNNING;
	while (*gameState == GameState::GAME_RUNNING) {

		SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(gameRenderer);

		//entity update methods
		shadow->update();
		pacman->update(gameState, collisionManager);
		

		SDL_RenderPresent(gameRenderer);
		SDL_Delay(100);
	}
	/*
	while (*gameState == GameState::EXIT_GAME) {

	}
	while(*gameState == GameState::GAME_PAUSED){}
	*/
}

