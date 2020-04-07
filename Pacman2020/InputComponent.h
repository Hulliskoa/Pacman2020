#pragma once

#include <vector>
#include <SDL.h>
#include <iostream>
#include "GameState.h"


class InputComponent
{
private:
	SDL_Event event{};
	const int speed = 8;

public:
	void update(SDL_Window* window, int speedXY[2], std::shared_ptr<GameState> gameState);
	InputComponent();
};
