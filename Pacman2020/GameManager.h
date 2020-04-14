#pragma once

#include <vector>
#include "MovingEntity.h"
#include "Pacman.h"
#include "Shadow.h"
#include "GameState.h"
#include "LevelManager.h"
#include <SDL_ttf.h>
#include "TextComponent.h"
/*! \brief
 *		Handles the different game states and creation of game objects
 *
 *
 *
 */
class GameManager
{

private:
	SDL_Window* window;
	SDL_Renderer* gameRenderer;
	SDL_Texture* spriteSheetTexture;

	int spriteSheetWidth;
	int spriteSheetHeight;
	int menuChoice = 0;/*!<Keeps track of which menu choice that is selected*/
	int currentLvl = 1;
	bool lvlLoaded = false;

	std::shared_ptr<TextComponent> startGameText;
	std::shared_ptr<TextComponent> quitGameText;
	std::shared_ptr<TextComponent> continueGameText;
	std::shared_ptr <std::string> menuInput = std::make_shared<std::string>();
	std::shared_ptr<InputComponent> m_input;/*!<InputComponent for handling menu inputs*/
	std::shared_ptr<CollisionManager> m_collisionManager;/*!<collision manager used throughout the program*/
	std::shared_ptr<GameState> gameState = std::make_shared<GameState>();/*!<Keeps track of game state*/
	std::shared_ptr<LevelManager> m_levelManager;/*!<A single level manager for creating and rendering levels*/
	std::shared_ptr<Shadow> shadow;
	std::shared_ptr<Pacman> pacman;

public:
	GameManager(SDL_Window* window, SDL_Renderer* renderer);
	void run();
	bool loadspriteSheetTexture(std::string path);
	void mainMenu();
	void inGame();


	void startGame();
	void exitGame();
	void pauseGame();

};


