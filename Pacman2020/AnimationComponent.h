#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

/**
AnimationComponent is responsible for rendering animations for all entities in the game.
Each entity object has a AnimationComponent for each animations they need. With the help of spritesheets  and SDL_Renderer this class can render all the sprites we need to create animations
*/
class AnimationComponent
{
private:
	int m_frame = 0;/*!< Used for keeping track of what sprite to render*/
	int m_numberOfFrames = 0;/*!< the number of frames the animation has*/
	std::vector<SDL_Rect> m_sprites;/*!< vector containing all sprites needed for the animation*/
	SDL_Texture* m_texture = nullptr; /*!< Texture used for drawing sprites in the SDL window*/
	//SDL_Renderer* renderer = nullptr;/*!< Main SDL_Renderer */
	int m_width = 0; /*!< width of the spritesheet in pixels. Used for rendering the correct sprites*/
	int m_height = 0;/*!< height of the spritesheet in pixels. Used for rendering the correct sprites*/

public:

	AnimationComponent();
	/**Constructor
	  \param numSprites an int that tells the AnimationComponent how many sprites will be used in this animation
	  \param texture SDL_Texture of the spritesheet textures used to show sprites on screen
	  \param textureWidth width of the spritesheet texture we will be using
	  \param textureHeight height of the spritesheet texture we will be using
	*/
	AnimationComponent(int numSprites, SDL_Texture* texture, int textureWidth, int textureHeight);
	~AnimationComponent();

	/**Adds SDL_Rect with coordinates and dimensions of target sprite to the m_sprites vector containing all sprites used for rendering the animation
	  \param xSpriteSheet takes the x coordinate of the sprite we want to render from the spritesheet.
	  \param ySpriteSheet takes the y coordinate of the sprite we want to render from the spritesheet.
	  \param w sprite width in pixels
	  \param h sprite height in pixels
	*/
	void addRect(int xSpriteSheet, int ySpriteSheet, int w, int h);

	/** Renders alle sprites contained in m_sprites vector using the m_frame member variable to count which sprite to render when
		\param x takes an int that represent the x coordinate of where we want the sprite to rendered inside the SDL_Window
		\param y takes an int that represent the y coordinate of where we want the sprite to rendered inside the SDL_Window
		\param renderer main renderer used to show sprites on screen
	*/
	void render(int x, int y, SDL_Renderer* renderer);
};
