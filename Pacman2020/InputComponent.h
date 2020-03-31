#pragma once
#include <vector>
#include <SDL.h>
#include <iostream>



class InputComponent
{
private:
	SDL_Event event{};
	int speedXY[2];
public:
	void update(SDL_Window* window, int speedXY[2]);
	int* getSpeed();
	InputComponent();
};
