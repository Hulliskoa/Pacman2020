#include "GameManager.h"


GameManager::GameManager(SDL_Window* window, SDL_Renderer* renderer) :
	window(window),
	gameRenderer(renderer)
{
	if (!loadspriteSheetTexture("..\\Pacman2020\\sprites\\spritesheet.png")) {
		std::cout << "could not load spritesheet" << std::endl;
	}

	
	collisionManager = std::make_shared<CollisionManager>();
	levelManager = std::make_shared<LevelManager>(gameRenderer);
	//shadow = std::make_shared<Shadow>(gameRenderer, spriteSheet, spriteSheetTexture, spriteSheetHeight, spriteSheetWidth);

	pacman = std::make_shared<Pacman>(window, spriteSheetTexture, spriteSheetHeight, spriteSheetWidth);





	//collisionManager->addEntity(shadow);
	collisionManager->addEntity(pacman);
	*gameState = GameState::GAME_STARTED;


}

void GameManager::run()
{

	while (*gameState == GameState::GAME_STARTED) {
		levelManager->readLevelFromTxt(currentLvl);
		levelManager->createLevel(collisionManager);
		*gameState = GameState::GAME_RUNNING;
		while (*gameState == GameState::GAME_RUNNING) {


			SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(gameRenderer);
			levelManager->renderLevel(gameRenderer);
			//entity update methods
			//shadow->update();
			pacman->update(gameState, collisionManager,gameRenderer);


			/*
			while (*gameState == GameState::LEVEL_COMPLETE) {
				//reset dots
				//reset positions for all entities
				//increment to next level
				//currentLvl++;
				*gameState == GAME_STARTED;
				

			}
			*/

			/*
			while (*gameState == GameState::GAME_PAUSED) {
				//display menu
				//freeze everything else
			SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(gameRenderer);

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

}
//source: http://lazyfoo.net/tutorials/SDL/07_texture_loading_and_rendering/index.php
bool GameManager::loadspriteSheetTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(gameRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			spriteSheetWidth = loadedSurface->w;
			spriteSheetHeight = loadedSurface->h;
		}
	}
	spriteSheetTexture = newTexture;
	return spriteSheetTexture != NULL;
}