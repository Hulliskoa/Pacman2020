#pragma once
#include <string>
#include <SDL.h>
#include <vector>

class Animation
{
public:

	Animation(SDL_Renderer* renderer);
	~Animation();

	//Loads image at specified path
	bool loadFromFile(std::string path);
	void addRect(int x, int y, int w, int h);

	//Gets image dimensions
	int getWidth();
	int getHeight();


	void render(int x, int y);

private:
	int counter = 0;
	int numberOfSprites = 0;
	//The actual hardware texture
	std::vector<SDL_Rect*> clips;
	SDL_Texture* mTexture;
	SDL_Renderer* gRenderer = NULL;
	//Image dimensions
	int mWidth = 0;
	int mHeight = 0;
};
