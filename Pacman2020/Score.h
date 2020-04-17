#pragma once
#include "Entity.h"
#include <SDL.h>

class Score
{
private:
	std::shared_ptr<AnimationComponent> zero;
	std::shared_ptr<AnimationComponent> one;
	std::shared_ptr<AnimationComponent> two;
	std::shared_ptr<AnimationComponent> three;
	std::shared_ptr<AnimationComponent> four;
	std::shared_ptr<AnimationComponent> five;
	std::shared_ptr<AnimationComponent> six;
	std::shared_ptr<AnimationComponent> seven;
	std::shared_ptr<AnimationComponent> eight;
	std::shared_ptr<AnimationComponent> nine;
	std::shared_ptr<AnimationComponent> highScore;


	std::shared_ptr<AnimationComponent> ghostPointsVisual;


	SDL_Texture* m_scoreTexture;
	SDL_Renderer* renderer;
	int m_textureWidth;
	int m_textureHeight;


public:

	Score(SDL_Renderer * gameRenderer);
	void update(int score);
	void renderGhostPoints(std::shared_ptr<Entity> pacman, int ghostPoints);
	bool loadspriteSheetTexture(std::string path);



};

