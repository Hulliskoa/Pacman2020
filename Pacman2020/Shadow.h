#pragma once
#include "Entity.h"
#include <SDL.h>

class Shadow :
	public Entity
{
private:
	int animationCounter = 0;
public:
	void update();
	Shadow(SDL_Renderer* renderer, SDL_Surface* mainSpriteSheet);
	~Shadow();

};

