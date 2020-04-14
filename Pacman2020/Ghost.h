#pragma once
#include "MovingEntity.h"
#include <SDL.h>
#include "Pacman.h"


class Ghost :
	public MovingEntity
{
private:
	int animationCounter = 0;
	std::shared_ptr<Pacman> pacman;
public:
	void update(SDL_Renderer* renderer);
	Ghost(SDL_Window* w, SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth);

};
