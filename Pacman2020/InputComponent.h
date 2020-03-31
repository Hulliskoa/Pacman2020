#pragma once
#include <vector>
#include <SDL.h>
#include "GameManager.h"


class InputComponent
{
private:
	int speedXY[2];

public:
	void update(SDL_Event event);
	int* getSpeed();
	InputComponent();
};
