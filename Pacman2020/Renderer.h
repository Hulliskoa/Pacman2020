#pragma once

#include <SDL_image.h>
#include <SDL.h>


class Renderer
{
	SDL_Window* window;

public:
	Renderer(SDL_Window* w);
	void renderSprite(int x, int y, Sprite source);
};

