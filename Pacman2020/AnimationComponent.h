#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

class AnimationComponent
{
private:
	int testF = 0;
	int m_frame = 0;
	int m_numberOfFrames = 0;
	std::vector<SDL_Rect> m_sprites;
	SDL_Texture* m_texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	int m_width = 0;
	int m_height = 0;

public:

	AnimationComponent();
	AnimationComponent(SDL_Renderer* renderer, int numFrames);
	~AnimationComponent();


	bool loadFromFile(SDL_Surface * mainSpriteSheet);
	void addRect(int xSpriteSheet, int ySpriteSheet, int w, int h);
	void free();
	void render(int x, int y);
	void renderTest(int x, int y, SDL_Texture* texture);

};
