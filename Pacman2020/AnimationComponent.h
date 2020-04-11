#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

/**
AnimationComponent is responsible for rendering animations for all entities in the game. 
Each entity object has a AnimationComponent for each animations they need.
*/
class AnimationComponent
{
private:
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
	
	/**
	Adds SDL_Rect with coordinates and dimensions of target sprite to the vector containing all sprites used for rendering the animation
	*/
	void addRect(int xSpriteSheet, int ySpriteSheet, int w, int h);
	void free();
	void render(int x, int y);

};
