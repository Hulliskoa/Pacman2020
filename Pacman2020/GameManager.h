#pragma once

#include <vector>
#include "Entity.h"
#include "Pacman.h"
#include "Shadow.h"
#include "GameState.h"
#include "LevelManager.h"



class GameManager
{

private:

	SDL_Window* window;
	SDL_Renderer* gameRenderer;
	SDL_Event* event{};
	SDL_Surface* spriteSheet;

	std::shared_ptr<CollisionManager> collisionManager;
	std::shared_ptr<GameState> gameState = std::make_shared<GameState>();
	std::shared_ptr<LevelManager> levelManager;
	std::shared_ptr<Shadow> shadow;
	std::shared_ptr<Pacman> pacman;

public:
	GameManager(SDL_Window* window, SDL_Renderer* renderer);

	void run();
	void startGame();
	void exitGame();
	void pauseGame();

};


