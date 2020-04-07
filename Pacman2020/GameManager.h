#pragma once

#include <vector>
#include "Pacman.h"
#include "Shadow.h"
#include "CollisionManager.h"
#include "GameState.h"



class GameManager
{

private:

	std::shared_ptr<GameState> gameState = std::make_shared<GameState>();
	bool quit = false;
	SDL_Window* window;
	SDL_Renderer* gameRenderer;
	SDL_Event* event{};
	SDL_Surface* spriteSheet;
	CollisionManager collisionManager;
	std::shared_ptr<Shadow> shadow;
	std::shared_ptr<Pacman> pacman;

public:
	GameManager(SDL_Window* window, SDL_Renderer* renderer);
	void run();
	void startGame();
	void exitGame();
	void pauseGame();

};


