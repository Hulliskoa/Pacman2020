#include "GameManager.h"
#include <thread>

using std::chrono::high_resolution_clock;
using namespace std::chrono_literals;
auto currentFrame = high_resolution_clock::now();
auto releaseTime = high_resolution_clock::now();

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

	shadow = std::make_shared<Ghost>(spriteSheetTexture, spriteSheetHeight, spriteSheetWidth, 0, 116, 120);
	shadow->rightAnimation->addRect(457, 65, 14, 14);
	shadow->rightAnimation->addRect(473, 65, 14, 14);

	shadow->setVelocity(4, 0);
	shadow->leftAnimation->addRect(489, 65, 14, 14);
	shadow->leftAnimation->addRect(505, 65, 14, 14);

	shadow->upAnimation->addRect(521, 65, 14, 14);
	shadow->upAnimation->addRect(537, 65, 14, 14);

	shadow->downAnimation->addRect(553, 65, 14, 14);
	shadow->downAnimation->addRect(569, 65, 14, 14);

	shadow->startAnimation->addRect(553, 65, 14, 14);
	shadow->startAnimation->addRect(553, 65, 14, 14);

	speedy = std::make_shared<Ghost>(spriteSheetTexture, spriteSheetHeight, spriteSheetWidth, 1, 132, 144);
	speedy->rightAnimation->addRect(457, 81, 14, 14);
	speedy->rightAnimation->addRect(473, 81, 14, 14);

	speedy->leftAnimation->addRect(489, 81, 14, 14);
	speedy->leftAnimation->addRect(505, 81, 14, 14);

	speedy->upAnimation->addRect(521, 81, 14, 14);
	speedy->upAnimation->addRect(537, 81, 14, 14);

	speedy->downAnimation->addRect(553, 81, 14, 14);
	speedy->downAnimation->addRect(569, 81, 14, 14);

	speedy->startAnimation->addRect(553, 81, 14, 14);
	speedy->startAnimation->addRect(553, 81, 14, 14);

	bashful = std::make_shared<Ghost>(spriteSheetTexture, spriteSheetHeight, spriteSheetWidth, 2, 116, 144);
	bashful->rightAnimation->addRect(457, 97, 14, 14);
	bashful->rightAnimation->addRect(473, 97, 14, 14);

	bashful->leftAnimation->addRect(489, 97, 14, 14);
	bashful->leftAnimation->addRect(505, 97, 14, 14);

	bashful->upAnimation->addRect(521, 97, 14, 14);
	bashful->upAnimation->addRect(537, 97, 14, 14);

	bashful->downAnimation->addRect(553, 97, 14, 14);
	bashful->downAnimation->addRect(569, 97, 14, 14);

	bashful->startAnimation->addRect(553, 97, 14, 14);
	bashful->startAnimation->addRect(553, 97, 14, 14);

	pokey = std::make_shared<Ghost>(spriteSheetTexture, spriteSheetHeight, spriteSheetWidth, 3, 100, 144);
	pokey->rightAnimation->addRect(457, 113, 14, 14);
	pokey->rightAnimation->addRect(473, 113, 14, 14);

	pokey->leftAnimation->addRect(489, 113, 14, 14);
	pokey->leftAnimation->addRect(505, 113, 14, 14);

	pokey->upAnimation->addRect(521, 113, 14, 14);
	pokey->upAnimation->addRect(537, 113, 14, 14);

	pokey->downAnimation->addRect(553, 113, 14, 14);
	pokey->downAnimation->addRect(569, 113, 14, 14);

	pokey->startAnimation->addRect(553, 113, 14, 14);
	pokey->startAnimation->addRect(553, 113, 14, 14);

	pacman = std::make_shared<Pacman>(spriteSheetTexture, spriteSheetHeight, spriteSheetWidth);
	//collisionManager->addEntity(shadow);

	startGameText = std::make_shared<TextComponent>("..\\Pacman2020\\fonts\\emulogic.ttf", "Start Game", 35, 50, gameRenderer);
	quitGameText = std::make_shared<TextComponent>("..\\Pacman2020\\fonts\\emulogic.ttf", "Quit Game", 35, 100, gameRenderer);
	continueGameText = std::make_shared<TextComponent>("..\\Pacman2020\\fonts\\emulogic.ttf", "Continue Game", 35, 50, gameRenderer);
	*gameState = GameState::MAIN_MENU;
}

void GameManager::run()
{
	int totalPellets = 0;

	while (*gameState == GameState::MAIN_MENU) {
		mainMenu();
		totalPellets = m_levelManager->pelletCount();
		while (*gameState == GameState::GAME_RUNNING) {
			inGame();
			auto lastFrame = currentFrame;
			high_resolution_clock::duration timespan = currentFrame - lastFrame;
			//std::cout << "DeltaT= " << timespan.count() << std::endl;
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
		m_levelManager->createLevel(m_collisionManager);
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
	auto lastFrame = currentFrame;
	currentFrame = high_resolution_clock::now();
	high_resolution_clock::duration timeSinceRelease = releaseTime - lastFrame;


	SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gameRenderer);

	m_levelManager->renderLevel();


	if (ghostsMovingOut && (3000ms + timeSinceRelease) <= 0ms) {
		speedy->aiComponent->removeTarget();
		bashful->aiComponent->removeTarget();
		pokey->aiComponent->removeTarget();
		ghostsMovingOut = false;
		m_levelManager->closeDoors();
	}

	if (m_levelManager->pelletCount() == ((m_levelManager->getStartingPelletCount()) - 29) + currentLvl) {
		releaseTime = high_resolution_clock::now();
		m_levelManager->openDoors();
		speedy->setVelocity(4, 0);
		bashful->setVelocity(-4, 0);
		pokey->setVelocity(-4, 0);

		speedy->aiComponent->setTarget(116, 120);
		bashful->aiComponent->setTarget(116, 120);
		pokey->aiComponent->setTarget(116, 120);
		ghostsMovingOut = true;



	}

	pacman->update(gameState, m_collisionManager, gameRenderer);
	shadow->update(gameRenderer, pacman, m_collisionManager);
	speedy->update(gameRenderer, pacman, m_collisionManager);
	bashful->update(gameRenderer, pacman, m_collisionManager);
	pokey->update(gameRenderer, pacman, m_collisionManager);


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
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));
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


