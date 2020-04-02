#pragma once

#include <vector>
#include "Pacman.h"



class GameManager
{

private:
	bool quit = false;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* event{};

	Pacman pacman;

public:
	GameManager(SDL_Window* window, SDL_Renderer * renderer);

	void run();
	void startGame();
	void exitGame();
	void pauseGame();

};


