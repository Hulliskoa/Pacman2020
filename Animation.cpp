#include "AnimationComponent.h"


AnimationComponent::AnimationComponent() {}

AnimationComponent::AnimationComponent(SDL_Renderer* renderer, std::string pathToSpritesheet, int numSprites) : renderer(renderer), numberOfFrames(numSprites) {}

AnimationComponent::~AnimationComponent()
{
	free();
}

bool AnimationComponent::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}



/**
	Adds SDL_Rect with coordinates and dimensions of target sprite to the animation object
*/
void AnimationComponent::addRect(int x, int y, int w, int h)
{
	SDL_Rect clip;
	clip.w = w;
	clip.h = h;
	clip.x = x;
	clip.y = y;
	clips.push_back(clip);
}

void AnimationComponent::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

int AnimationComponent::getWidth()
{
	return mWidth;
}

int AnimationComponent::getHeight()
{
	return mHeight;;
}

void AnimationComponent::render(int x, int y)
{
	SDL_Rect clip = clips[frame];
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (&clip != NULL)
	{
		renderQuad.w = clip.w;
		renderQuad.h = clip.h;
	}
	SDL_RenderCopy(renderer, mTexture, &clip, &renderQuad);

	frame++;

	if (frame == numberOfFrames) {
		frame = 0;
	}

}
