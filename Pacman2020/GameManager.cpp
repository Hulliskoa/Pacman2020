#include "GameManager.h"


GameManager::GameManager(SDL_Window* window, SDL_Renderer* renderer) :
	window(window),
	gameRenderer(renderer)
{

	//Pre-loading spritesheet in gameManager to save memory when loading sprites for all moving entities
	if (!loadspriteSheetTexture("..\\Pacman2020\\sprites\\spritesheet.png")) {
		std::cout << "could not load spritesheet" << std::endl;
	}

	m_input = std::make_shared <InputComponent>();
	m_collisionManager = std::make_shared<CollisionManager>();
	m_levelManager = std::make_shared<LevelManager>(gameRenderer);
	shadow = std::make_shared<Ghost>(spriteSheetTexture, spriteSheetHeight, spriteSheetWidth);

	pacman = std::make_shared<Pacman>(spriteSheetTexture, spriteSheetHeight, spriteSheetWidth);
	//collisionManager->addEntity(shadow);

	startGameText = std::make_shared<TextComponent>("..\\Pacman2020\\fonts\\emulogic.ttf", "Start Game", 35, 50, gameRenderer);
	quitGameText = std::make_shared<TextComponent>("..\\Pacman2020\\fonts\\emulogic.ttf", "Quit Game", 35, 100, gameRenderer);
	continueGameText = std::make_shared<TextComponent>("..\\Pacman2020\\fonts\\emulogic.ttf", "Continue Game", 35, 50, gameRenderer);
	*gameState = GameState::MAIN_MENU;
}

void GameManager::run()
{

	while (*gameState == GameState::MAIN_MENU) {
		mainMenu();

		while (*gameState == GameState::GAME_RUNNING) {
			inGame();
		}
		/*
		while (*gameState == GameState::EXIT_GAME) {

		}

		*/
	}

}


void GameManager::mainMenu()
{


	if (!lvlLoaded) {
		m_collisionManager->clearEntityArray();
		m_levelManager->readLevelFromTxt(currentLvl);
		m_levelManager->createLevel2(m_collisionManager);
		m_levelManager->createInterSections(m_collisionManager);
		m_collisionManager->addEntity(pacman);
		lvlLoaded = true;
	}

	//Checks button push in main menu;
	*menuInput = m_input->mainUpdate(gameState);

	SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gameRenderer);

	//Renders main menu;
	startGameText->renderText(gameRenderer, 0);
	quitGameText->renderText(gameRenderer, 0);

	//continueGameText->renderText(gameRenderer, 0);

	if (menuChoice == 0) {
		startGameText->renderText(gameRenderer, 1);
	}
	if (menuChoice == 1) {
		quitGameText->renderText(gameRenderer, 1);
	}

	SDL_RenderPresent(gameRenderer);


	if (*menuInput == "DOWN") {
		menuChoice = menuChoice == 1 ? 0 : 1;
	}
	else if (*menuInput == "UP") {
		menuChoice = menuChoice == 0 ? 1 : 0;
	}


	if (*menuInput == "RETURN" && menuChoice == 0) {
		*gameState = GameState::GAME_RUNNING;
	}
	if (*menuInput == "RETURN" && menuChoice == 1) {
		*gameState = GameState::EXIT_GAME;
	}


}

void GameManager::inGame() {

	SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gameRenderer);

	m_levelManager->renderLevel();
	//entity update methods
	//shadow->update();
	pacman->update(gameState, m_collisionManager, gameRenderer);
	shadow->update(gameRenderer, pacman, m_collisionManager);

	/*
	while (*gameState == GameState::LEVEL_COMPLETE) {
	lvlLoaded = false;
		//reset dots
		//reset positions for all entities
		//increment to next level
		//currentLvl++;
		*gameState == GAME_STARTED;
		//levelManager->readLevelFromTxt(currentLvl);

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


