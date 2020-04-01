#pragma once

#include <SDL_image.h>
#include <SDL.h>
#include "Sprite.h"


class Renderer
{
	SDL_Window* window;

public:
	Renderer(SDL_Window* w);
	
	void renderMap();
};

