#pragma once


#include <iostream>
#include <SDL.h>
#include "InputComponent.h"
#include "AnimationComponent.h"
#include "MovingEntity.h"
#include "GameState.h"
#include "Score.h"
#include "CollisionManager.h"
#include "SoundComponent.h"
#include "InputComponent.h"

class Pacman : public MovingEntity
{
private:
	std::shared_ptr<InputComponent> m_input;

	std::shared_ptr<Score> scoreComponent;
	std::shared_ptr<SoundComponent> m_pelletMunch;
	std::shared_ptr<SoundComponent> m_fruitMunch;
	std::shared_ptr<SoundComponent> m_ghostMunch;
	std::shared_ptr<SoundComponent> m_deathSound;
	std::shared_ptr<AnimationComponent> deathAnimation;
	std::shared_ptr<AnimationComponent> lastAnimation = nullptr;
	int score = 0;
	int remainingLife = 3;
	int ghostPoints = 100;
	int pointDoubler = 2;

public:
	void update(std::shared_ptr<GameState> gameState, std::shared_ptr<CollisionManager> collisionManager, SDL_Renderer* renderer);
	Pacman(SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth, SDL_Renderer* renderer);
	int getScore();
	void resetScore();
	void lostLife();
	int getRemainingLives();
	~Pacman();

};

