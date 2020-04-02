#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

class AnimationComponent
{
public:

	AnimationComponent();
	AnimationComponent(SDL_Renderer* renderer, std::string pathToSpriteSheet, int numFrames);
	~AnimationComponent();

	bool loadFromFile(std::string path);
	void addRect(int x, int y, int w, int h);
	void free();
	void render(int x, int y);

	int getWidth();
	int getHeight();

private:
	int frame = 0;
	int numberOfFrames = 0;
	std::vector<SDL_Rect> clips;
	SDL_Texture* mTexture = nullptr;
	SDL_Renderer* renderer = nullptr;
	int m_width = 0;
	int m_height = 0;
};
