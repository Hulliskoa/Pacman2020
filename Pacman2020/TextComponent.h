#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

class TextComponent
{
private:
	std::vector<SDL_Texture*> texts;
	TTF_Font* m_font;
	

	SDL_Texture* m_message2;
	SDL_Rect message_rect;
	SDL_Color color;
	std::string m_text;
	SDL_Renderer* m_mainRenderer;


public:
	TextComponent(std::string fontPath, std::string text, int xCoord, int yCoord, SDL_Renderer* renderer);
	void renderText(SDL_Renderer* renderer, int position);
	void switchColor();
};

