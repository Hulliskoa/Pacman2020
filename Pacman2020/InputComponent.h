#pragma once
#include <vector>
#include <SDL.h>
#include <iostream>


class InputComponent
{
private:
	SDL_Event event{};
	const int speed = 8;

public:
	void update(SDL_Window* window, int speedXY[2]);
	InputComponent();
};
