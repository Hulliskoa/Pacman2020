#pragma once
#include "Entity.h"
#include <SDL.h>
/*! \brief
 *		Component for rendering score to screen
 *
 *
 * 
 */
class ScoreComponent
{
private:
	/*!<Animations for numbers in score counter*/
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

	SDL_Texture* m_scoreTexture;/*!<Animations for numbers in score counter*/
	SDL_Renderer* renderer;
	int m_textureWidth;
	int m_textureHeight;

public:

	ScoreComponent(SDL_Renderer* gameRenderer);

	/**
	Updates current score
		\param score number that will we shown on the score ingame
	*/
	void update(int score);

	/**
		Load the spritesheet that is going to be used for rendering on screen
		\param path path to sprite sheet we want to use
	*/
	bool loadspriteSheetTexture(std::string path);



};

