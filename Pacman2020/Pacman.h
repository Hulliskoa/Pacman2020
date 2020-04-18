#pragma once


#include <iostream>
#include <SDL.h>
#include "InputComponent.h"
#include "AnimationComponent.h"
#include "MovingEntity.h"
#include "GameState.h"
#include "ScoreComponent.h"
#include "CollisionManager.h"
#include "SoundComponent.h"
#include "InputComponent.h"

/*! \brief
 *		 child class of MovingEntity and contains all Pacman specific member variables and methods
 *
 */

class Pacman : public MovingEntity
{
private:
	std::shared_ptr<InputComponent> m_input;

	std::shared_ptr<ScoreComponent> m_scoreComponent;/*!<Is responsible for rendering score to screen*/
	std::shared_ptr<SoundComponent> m_pelletMunch;
	std::shared_ptr<SoundComponent> m_fruitMunch;
	std::shared_ptr<SoundComponent> m_ghostMunch;
	std::shared_ptr<SoundComponent> m_deathSound;
	std::shared_ptr<AnimationComponent> m_deathAnimation;
	std::shared_ptr<AnimationComponent> m_lastAnimation = nullptr;
	int m_score = 0;/*!<keeps track of score*/
	int m_remainingLife = 3;
	int m_ghostPoints = 100;
	int m_pointDoubler = 2;

public:

	void update(std::shared_ptr<GameState> gameState, std::shared_ptr<CollisionManager> collisionManager, SDL_Renderer* renderer);
	Pacman(SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth, SDL_Renderer* renderer);
	/**
		returns m_score
	*/
	int getScore();
	/**
		resets m_score to 0
	*/
	void resetScore();
	/**
		reduce m_remainingLife by 1
	*/
	void lostLife();
	/**
		returns m_remainingLife
	*/
	int getRemainingLives();
	~Pacman();

};

