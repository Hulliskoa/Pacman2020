#pragma once
#include "Pacman.h"
#include <SDL.h>

class Score :
	public Entity
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


	SDL_Texture * m_scoreTexture;
	SDL_Renderer* gameRenderer;
	int m_textureWidth;
	int m_textureHeight;


public:

	Score(SDL_Renderer* renderer);
	void update(std::shared_ptr<Pacman> pacman);
	bool loadspriteSheetTexture(std::string path);



};

