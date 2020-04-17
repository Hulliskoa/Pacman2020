#pragma once

#include <vector>
#include "MovingEntity.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GameState.h"
#include "LevelManager.h"
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "SoundComponent.h"
/*! \brief
 *		Handles the game loop, stores the different game states and creates game objects
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
	int currentMap = 1;
	bool lvlLoaded = false;
	bool ghostsMovingOut = false;
	bool startedFleeing = false;

	std::shared_ptr<TextComponent> startGameText;/*!<TextComponent for static text in menus*/
	std::shared_ptr<TextComponent> quitGameText;/*!<TextComponent for static text in menus*/
	std::shared_ptr<TextComponent> continueGameText;/*!<TextComponent for static text in menus*/
	std::shared_ptr<TextComponent> gameOverText;/*!<TextComponent for static text in menus*/
	std::shared_ptr <std::string> menuInput = std::make_shared<std::string>();
	std::shared_ptr<InputComponent> m_input;/*!<InputComponent for handling menu inputs*/
	std::shared_ptr<CollisionManager> m_collisionManager;/*!<collision manager used throughout the program*/
	std::shared_ptr<GameState> gameState = std::make_shared<GameState>();/*!<Keeps track of game state*/
	std::shared_ptr<LevelManager> m_levelManager;/*!<A single level manager for creating and rendering levels*/
	std::shared_ptr<SoundComponent> m_introMusic;/*!<A single level manager for creating and rendering levels*/
	std::shared_ptr<SoundComponent> m_intermission;/*!<A single level manager for creating and rendering levels*/

	std::shared_ptr<Ghost> shadow;
	std::shared_ptr<Ghost> speedy;
	std::shared_ptr<Ghost> bashful;
	std::shared_ptr<Ghost> pokey;
	std::shared_ptr<Pacman> pacman;

public:
	GameManager(SDL_Window* window, SDL_Renderer* renderer);
	void run();
	bool loadspriteSheetTexture(std::string path);
	void mainMenu();
	void inGame();
	void nextLvl();
	void gameOver();

	void startGame();
	void exitGame();
	void pauseGame();


};


