#pragma once
#include "MovingEntity.h"
#include <SDL.h>

class Shadow :
	public MovingEntity
{
private:
	int animationCounter = 0;
public:
	void update();
	Shadow(SDL_Renderer* renderer, SDL_Surface* mainSpriteSheet);
	~Shadow();

};

