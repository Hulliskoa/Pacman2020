#include "AnimationComponent.h"

//Source: LazyFoo tutorial - http://lazyfoo.net/tutorials/SDL/11_clip_rendering_and_sprite_sheets/index.php

//AnimationComponent::AnimationComponent() {}

AnimationComponent::AnimationComponent()
{
}

AnimationComponent::AnimationComponent(int numSprites, SDL_Texture* texture, int textureWidth, int textureHeight) :
	m_numberOfFrames(numSprites), m_texture(texture), m_width(textureWidth), m_height(textureHeight) {}

AnimationComponent::~AnimationComponent()
{
	if (m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_width = 0;
		m_height = 0;
	}
}




void AnimationComponent::addRect(int xSpriteSheet, int ySpriteSheet, int w, int h)
{
	SDL_Rect clip;
	clip.w = w;
	clip.h = h;
	clip.x = xSpriteSheet;
	clip.y = ySpriteSheet;
	m_sprites.push_back(clip);
}

void AnimationComponent::render(int x, int y, SDL_Renderer* renderer)
{
	SDL_Rect clip = m_sprites[m_frame];
	SDL_Rect renderQuad = { x - (clip.w / 2), y - (clip.h / 2), m_width, m_height };


	if (&clip != NULL)
	{
		renderQuad.w = clip.w;
		renderQuad.h = clip.h;
	}


	SDL_RenderCopy(renderer, m_texture, &clip, &renderQuad);

	m_frame++;



	if (m_frame >= m_numberOfFrames) {
		m_frame = 0;
	}

}