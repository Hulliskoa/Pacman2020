#pragma once
#include "AnimationComponent.h"
#include <SDL.h>


class HPComponent
{

private:
	std::shared_ptr<AnimationComponent> m_firstLife;
	std::shared_ptr<AnimationComponent> m_secondLife;
	std::shared_ptr<AnimationComponent> m_thirdLife;

	SDL_Texture* m_hpTexture;/*!<Animations for numbers in score counter*/
	SDL_Renderer* renderer;
	int m_textureWidth;
	int m_textureHeight;
public:
	HPComponent(SDL_Renderer* mainRenderer);
	void update(int life);

	/**
		Load the spritesheet that is going to be used for rendering on screen
		\param path path to sprite sheet we want to use
	*/
	bool loadspriteSheetTexture(std::string path);
};

