#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

class Animation
{
public:

	Animation();
	Animation(SDL_Renderer* renderer, std::string pathToSpriteSheet, int numFrames);
	~Animation();

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
	SDL_Renderer* gRenderer = nullptr;
	int mWidth = 0;
	int mHeight = 0;
};
