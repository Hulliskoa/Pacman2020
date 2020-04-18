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
 *	The different parts of the game is split in to different methods e.g mainMenu, inGame and so on.
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
	int currentLvl = 1;/*!<Keeps track of the current level*/
	int currentMap = 1;/*!<Keeps track of the current map to be loaded*/
	bool lvlLoaded = false;/*!<Boolean for checking if the current lvl is loaded*/
	bool ghostsMovingOut = false; /*!<Boolean for checking if the ghost ar moving out of the cage*/
	bool startedFleeing = false; /*!<Boolean for checking if the ghost started fleeing and then being able to set a timer*/

	std::shared_ptr<TextComponent> startGameText;/*!<TextComponent for static text in menus*/
	std::shared_ptr<TextComponent> quitGameText;/*!<TextComponent for static text in menus*/
	std::shared_ptr<TextComponent> continueGameText;/*!<TextComponent for static text in menus*/
	std::shared_ptr<TextComponent> gameOverText;/*!<TextComponent for static text in menus*/
	std::shared_ptr <std::string> menuInput = std::make_shared<std::string>();
	std::shared_ptr<InputComponent> m_input;/*!<InputComponent for handling menu inputs*/
	std::shared_ptr<CollisionManager> m_collisionManager;/*!<collision manager used throughout the program*/
	std::shared_ptr<GameState> gameState = std::make_shared<GameState>();/*!<Keeps track of game state*/
	std::shared_ptr<LevelManager> m_levelManager;/*!<A single level manager for creating and rendering levels*/
	std::shared_ptr<SoundComponent> m_introMusic;/*!<SoundComponent for the intro music*/
	std::shared_ptr<SoundComponent> m_intermission;/*!<SoundComponent for the intermission music*/

	std::shared_ptr<Ghost> shadow;
	std::shared_ptr<Ghost> speedy;
	std::shared_ptr<Ghost> bashful;
	std::shared_ptr<Ghost> pokey;
	std::shared_ptr<Pacman> pacman;

public:
	/**Constructor
		\param window the main SDL window created in the main method.
		\param renderer the main renderer created in the main method and used throughout the game
	*/
	GameManager(SDL_Window* window, SDL_Renderer* renderer);
	
	/**The game loop*/
	void run();
	/**Loads the main spritesheet used for rendering moving objects
		\param path path to spritesheet png file
	*/
	bool loadspriteSheetTexture(std::string path);

	/**Handles text rendering and input from user in main menu*/
	void mainMenu();

	/**The actual game with update methods for all game objects and also the different game state while in game*/
	void inGame();

	/**Handles the intermission between each level*/
	void nextLvl();

	/**Handles the exit process of the game*/
	void gameOver();


};


