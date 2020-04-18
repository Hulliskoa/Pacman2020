#include "GameManager.h"
#include <thread>

using std::chrono::high_resolution_clock;
using namespace std::chrono_literals;
auto currentFrame = high_resolution_clock::now();
auto releaseTime = high_resolution_clock::now();
auto fleeStart = high_resolution_clock::now();
auto deathTimer = high_resolution_clock::now();

GameManager::GameManager(SDL_Window* window, SDL_Renderer* renderer) :
	window(window),
	gameRenderer(renderer)
{

	//Pre-loading spritesheet in gameManager to save memory when loading sprites for all moving entities
	if (!loadspriteSheetTexture("..\\Pacman2020\\sprites\\spritesheet.png")) {
		std::cout << "could not load spritesheet" << std::endl;
	}
	//loading member objects
	m_input = std::make_shared <InputComponent>();
	m_collisionManager = std::make_shared<CollisionManager>();
	m_levelManager = std::make_shared<LevelManager>(gameRenderer);
	m_introMusic = std::make_shared<SoundComponent>("..\\Pacman2020\\sounds\\pacman_beginning.wav");
	m_intermission = std::make_shared<SoundComponent>("..\\Pacman2020\\sounds\\pacman_intermission.wav");
	//Creates ghost objects and add sprites to animation components
	shadow = std::make_shared<Ghost>(spriteSheetTexture, spriteSheetHeight, spriteSheetWidth, 0, 116, 120);
	shadow->rightAnimation->addRect(457, 65, 14, 14);
	shadow->rightAnimation->addRect(473, 65, 14, 14);
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

	pacman = std::make_shared<Pacman>(spriteSheetTexture, spriteSheetHeight, spriteSheetWidth, gameRenderer);
	pacman->setBaseSpeed(4);
	m_collisionManager->addMovingEntity(pacman);
	m_collisionManager->addMovingEntity(shadow);
	m_collisionManager->addMovingEntity(bashful);
	m_collisionManager->addMovingEntity(speedy);
	m_collisionManager->addMovingEntity(pokey);

	//creates text components for the menu
	startGameText = std::make_shared<TextComponent>("..\\Pacman2020\\fonts\\emulogic.ttf", "Start Game", 65, 80, 100, 10, gameRenderer, 30);
	quitGameText = std::make_shared<TextComponent>("..\\Pacman2020\\fonts\\emulogic.ttf", "Quit Game", 65, 100, 100, 10, gameRenderer, 30);
	continueGameText = std::make_shared<TextComponent>("..\\Pacman2020\\fonts\\emulogic.ttf", "Next Level", 65, 80, 100, 10, gameRenderer, 30);
	gameOverText = std::make_shared<TextComponent>("..\\Pacman2020\\fonts\\emulogic.ttf", "Game Over", 40, 40, 150, 30, gameRenderer, 30);
	*gameState = GameState::MAIN_MENU;
}

void GameManager::run()
{
	while (*gameState == GameState::MAIN_MENU) {
		mainMenu();
		while (*gameState == GameState::GAME_RUNNING || *gameState == GameState::GAME_RUNNING_FLEE
			|| *gameState == GameState::GAME_RUNNING_FLEE_ENDING || *gameState == GameState::RESTART_LEVEL
			|| *gameState == GameState::PACMAN_DIED || *gameState == GameState::GAME_OVER) {

			inGame();

			while (*gameState == GameState::LEVEL_COMPLETE) {
				nextLvl();
			}
			while (*gameState == GameState::GAME_OVER) {
				gameOver();
			}
		}
	}
}

void GameManager::mainMenu()
{
	if (!lvlLoaded) {
		m_collisionManager->clearEntityArray();
		m_levelManager->createLevel(m_collisionManager);
		m_levelManager->createInterSections(m_collisionManager);

		lvlLoaded = true;
	}
	m_introMusic->play(-1, 0, 30);
	//Checks button push in main menu;
	*menuInput = m_input->mainUpdate(gameState);

	//Renders main menu;
	startGameText->renderText(0);
	quitGameText->renderText( 0);

	if (menuChoice == 0) {
		startGameText->renderText(1);
	}
	if (menuChoice == 1) {
		quitGameText->renderText(1);
	}

	if (*menuInput == "DOWN") {
		menuChoice = menuChoice == 1 ? 0 : 1;
	}
	else if (*menuInput == "UP") {
		menuChoice = menuChoice == 0 ? 1 : 0;
	}

	if (*menuInput == "RETURN" && menuChoice == 0) {
		*gameState = GameState::GAME_RUNNING;
		m_introMusic->fadeOut();
	}
	if (*menuInput == "RETURN" && menuChoice == 1) {
		*gameState = GameState::EXIT_GAME;

	}
	SDL_RenderPresent(gameRenderer);

}
//Main gameloop
void GameManager::inGame() {
	auto lastFrame = currentFrame;
	currentFrame = high_resolution_clock::now();

	high_resolution_clock::duration timeSinceRelease = releaseTime - lastFrame;
	high_resolution_clock::duration timeSinceFlee = fleeStart - currentFrame;
	high_resolution_clock::duration timeSpan = currentFrame - lastFrame;
	high_resolution_clock::duration timeSinceDeath = deathTimer - lastFrame;

	SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gameRenderer);

	m_levelManager->renderLevel(gameRenderer);
	pacman->update(gameState, m_collisionManager, gameRenderer);



	if (m_levelManager->pelletCount() == ((m_levelManager->getStartingPelletCount()) - 29) + m_levelManager->getCurrentLevel()) {
		releaseTime = high_resolution_clock::now();
		m_levelManager->openDoors();

		speedy->setEntityType(EntityType::GHOST_RETURN);
		bashful->setEntityType(EntityType::GHOST_RETURN);
		pokey->setEntityType(EntityType::GHOST_RETURN);

		speedy->aiComponent->setTarget(112, 120);
		bashful->aiComponent->setTarget(112, 120);
		pokey->aiComponent->setTarget(112, 120);
		m_levelManager->closeDoors();
		ghostsMovingOut = true;
	}

	//ending flee
	if (startedFleeing == true && (3000ms + timeSinceFlee) <= 0ms) {
		*gameState = GameState::GAME_RUNNING_FLEE_ENDING;
	}

	if (startedFleeing == true && (5000ms + timeSinceFlee) <= 0ms && *gameState == GameState::GAME_RUNNING_FLEE_ENDING) {
		speedy->aiComponent->removeTarget();
		bashful->aiComponent->removeTarget();
		pokey->aiComponent->removeTarget();
		shadow->aiComponent->removeTarget();
		*gameState = GameState::GAME_RUNNING;
		startedFleeing = false;
	}

	//starting flee
	if (*gameState == GameState::GAME_RUNNING_FLEE && startedFleeing == false) {
		fleeStart = high_resolution_clock::now();
		speedy->aiComponent->setTarget(10, 10);
		bashful->aiComponent->setTarget(10, 880);
		pokey->aiComponent->setTarget(670, 880);
		shadow->aiComponent->setTarget(670, 10);
		startedFleeing = true;
	}
	//Level complete
	if (m_levelManager->pelletCount() == 0) {
		lvlLoaded = false;
		if (m_levelManager->getCurrentLevel() % 10 == 2) {
			shadow->increaseSpeed();
			pokey->increaseSpeed();
			bashful->increaseSpeed();
			speedy->increaseSpeed();
		}

		*gameState = GameState::LEVEL_COMPLETE;
	}

	if (*gameState == GameState::PACMAN_DIED) {
		pacman->setVelocity(0, 0);
		speedy->setVelocity(0, 0);
		bashful->setVelocity(0, 0);
		pokey->setVelocity(0, 0);
		shadow->setVelocity(0, 0);

	}

	if (*gameState == GameState::RESTART_LEVEL) {
		pacman->setCoordinates(104, 216);
		shadow->setCoordinates(116, 120);
		speedy->setCoordinates(132, 144);
		bashful->setCoordinates(116, 144);
		pokey->setCoordinates(100, 144);
		speedy->setVelocity(1, 0);
		bashful->setVelocity(1, 0);
		pokey->setVelocity(1, 0);
		shadow->setVelocity(1, 0);
		*gameState = GameState::GAME_RUNNING;
	}
	if(*gameState == GameState::GAME_OVER){
		lvlLoaded = false;
	}
	shadow->update(gameState, gameRenderer, pacman, m_collisionManager);
	speedy->update(gameState, gameRenderer, pacman, m_collisionManager);
	bashful->update(gameState, gameRenderer, pacman, m_collisionManager);
	pokey->update(gameState, gameRenderer, pacman, m_collisionManager);




	std::this_thread::sleep_for(50ms - std::chrono::duration_cast<std::chrono::milliseconds>(currentFrame - high_resolution_clock::now()));
	SDL_RenderPresent(gameRenderer);
}
//code for handling loading of next level after all pellets have been eaten
void GameManager::nextLvl()
{
	m_intermission->play(1, 0, 30);
	if (!lvlLoaded) {

		SDL_RenderClear(gameRenderer);
		m_collisionManager->clearEntityArray();

		m_levelManager->createLevel(m_collisionManager);
		m_levelManager->createInterSections(m_collisionManager);

		pacman->setVelocity(0, 0);
		pacman->setCoordinates(104, 216);

		shadow->setCoordinates(116, 120);
		speedy->setCoordinates(132, 144);
		bashful->setCoordinates(116, 144);
		pokey->setCoordinates(100, 144);
		speedy->setVelocity(0, 0);
		bashful->setVelocity(0, 0);
		pokey->setVelocity(0, 0);
		shadow->setVelocity(1, 0);
		lvlLoaded = true;
	}

	SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gameRenderer);

	//Checks button push in menu;
	*menuInput = m_input->mainUpdate(gameState);

	continueGameText->renderText(0);
	quitGameText->renderText(0);

	//switch color
	if (menuChoice == 0) {
		continueGameText->renderText(1);
	}
	if (menuChoice == 1) {
		quitGameText->renderText(1);
	}

	if (*menuInput == "DOWN") {
		menuChoice = menuChoice == 1 ? 0 : 1;
	}
	else if (*menuInput == "UP") {
		menuChoice = menuChoice == 0 ? 1 : 0;
	}

	if (*menuInput == "RETURN" && menuChoice == 0) {
		*gameState = GameState::GAME_RUNNING;
		m_introMusic->fadeOut();
	}
	if (*menuInput == "RETURN" && menuChoice == 1) {
		*gameState = GameState::EXIT_GAME;
	}
	SDL_RenderPresent(gameRenderer);
}

void GameManager::gameOver()
{

	if (!lvlLoaded) {
		m_collisionManager->clearEntityArray();
		m_levelManager->resetLevels();
		pacman->resetScore();
		m_levelManager->createLevel(m_collisionManager);
		m_levelManager->createInterSections(m_collisionManager);
		pacman->setCoordinates(104, 216);
		shadow->setCoordinates(116, 120);
		speedy->setCoordinates(132, 144);
		bashful->setCoordinates(116, 144);
		pokey->setCoordinates(100, 144);
		speedy->setVelocity(1, 0);
		bashful->setVelocity(1, 0);
		pokey->setVelocity(1, 0);
		shadow->setVelocity(1, 0);
		lvlLoaded = true;
	}

	//Checks button push in menu;
	*menuInput = m_input->mainUpdate(gameState);

	SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gameRenderer);

	//Renders main menu;
	startGameText->renderText(0);
	quitGameText->renderText(0);
	gameOverText->renderText(0);

	//switch color
	if (menuChoice == 0) {
		startGameText->renderText(1);
	}
	if (menuChoice == 1) {
		quitGameText->renderText(1);
	}

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
	SDL_RenderPresent(gameRenderer);

}


//source: http://lazyfoo.net/tutorials/SDL/07_texture_loading_and_rendering/index.php
bool GameManager::loadspriteSheetTexture(std::string path)
{

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		//Color keying black to make the background transparent when rendering sprites
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


