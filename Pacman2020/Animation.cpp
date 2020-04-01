#include "Animation.h"



Animation::Animation(SDL_Renderer* renderer) : mWidth(680), mHeight(248)
{

}

void Animation::addRect(int x, int y, int w, int h)
{
	SDL_Rect clip;
}

void Animation::render(int x, int y)
{
	SDL_Rect* clip = clips[counter];
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}
