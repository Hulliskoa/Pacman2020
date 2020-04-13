#pragma once
#include "MovingEntity.h"
#include <SDL.h>

class Shadow :
	public MovingEntity
{
private:
	int animationCounter = 0;
public:
	void update(SDL_Renderer* renderer);
	Shadow(SDL_Window* w, SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth);
	~Shadow();

};

