#pragma once


#include <iostream>
#include <SDL.h>
#include "InputComponent.h"
#include "AnimationComponent.h"
#include "MovingEntity.h"
#include "GameState.h"
#include "CollisionManager.h"

class Pacman : public MovingEntity
{
private:
	std::shared_ptr<AnimationComponent> deathAnimation;
	std::shared_ptr<AnimationComponent> lastAnimation = nullptr;
	int score = 0;
	int remainingLife = 3;
	int ghostPoints = 100;
	int pointDoubler = 2;

public:
	void update(std::shared_ptr<GameState> gameState, std::shared_ptr<CollisionManager> collisionManager, SDL_Renderer* renderer);
	Pacman(SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth);
	int getScore();
	int getRemainingLives();
	~Pacman();

};

