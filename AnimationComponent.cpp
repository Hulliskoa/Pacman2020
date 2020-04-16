#include "AnimationComponent.h"

//Source: LazyFoo tutorial - http://lazyfoo.net/tutorials/SDL/11_clip_rendering_and_sprite_sheets/index.php

AnimationComponent::AnimationComponent() {}

AnimationComponent::AnimationComponent(SDL_Renderer* renderer, std::string pathToSpritesheet, int numSprites) : renderer(renderer), numberOfFrames(numSprites) {}

AnimationComponent::~AnimationComponent()
{
	free();
}

bool AnimationComponent::loadFromFile(std::string path)
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	m_texture = newTexture;
	return m_texture != NULL;
}



/**
	Adds SDL_Rect with coordinates and dimensions of target sprite to the vector containing all sprites for the animation
*/
void AnimationComponent::addRect(int x, int y, int w, int h)
{
	SDL_Rect clip;
	clip.w = w;
	clip.h = h;
	clip.x = x;
	clip.y = y;
	sprites.push_back(clip);
}

void AnimationComponent::free()
{
	if (m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_width = 0;
		m_height = 0;
	}
}

int AnimationComponent::getWidth()
{
	return m_width;
}

int AnimationComponent::getHeight()
{
	return m_height;;
}

void AnimationComponent::render(int x, int y)
{
	SDL_Rect clip = sprites[frame];
	SDL_Rect renderQuad = { x, y, m_width, m_height };

	if (&clip != NULL)
	{
		renderQuad.w = clip.w;
		renderQuad.h = clip.h;
	}
	SDL_RenderCopy(renderer, m_texture, &clip, &renderQuad);

	frame++;

	if (frame == numberOfFrames) {
		frame = 0;
	}

}
