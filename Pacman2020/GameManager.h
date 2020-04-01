#pragma once

#include <vector>
#include "Pacman.h"


//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern







class GameManager
{

private:
	bool quit = false;
	SDL_Window* w;
	SDL_Event event{};
	Pacman pacman;

public:
	GameManager(SDL_Window* window);

	void run();
	void startGame();
	void exitGame();
	void pauseGame();

};


