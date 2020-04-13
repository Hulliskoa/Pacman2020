// Pacman2020.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>//source: http://www.sdltutorials.com/sdl-ttf
#include <stdio.h>
#include "GameManager.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 900;


bool init(SDL_Window** window, SDL_Renderer** renderer) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		*window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (*window == NULL)
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}
		else
		{

			*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
			if (*renderer == NULL)
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				return false;
			}
			else
			{
				//Scales render by 2 so that it looks larger and more retro
				SDL_RenderSetScale(*renderer, 3, 3);
				SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0x00);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
					return false;
				}
				else {
					if (TTF_Init() < 0) {
						std::cout << "SDL_TTF could not initialize!" << std::endl;
					}
					return true;
				}
				
			}
		}
	}
}

int main(int argc, char* argv[])
{
	//TODO: Legge dette inn i funksjoner

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	//Initialize SDL
	if (!init(&window, &renderer)) {
		std::cout << "could not initialize SDL" << std::endl;
	}

	std::shared_ptr<GameManager> gm = std::make_shared<GameManager>(window, renderer);
	gm->run();


	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	TTF_Quit();
	SDL_Quit();

	return 0;
}

