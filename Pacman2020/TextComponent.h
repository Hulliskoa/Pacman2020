#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
/*! \brief
 *		Wrapper object for showing text on screen
 *
 *
 * It saves two versions of the same text to be able to switch between white and purple text
 */
class TextComponent
{
private:
	std::vector<SDL_Texture*> texts;
	TTF_Font* m_font;
	SDL_Rect message_rect;
	SDL_Color color;
	std::string m_text;
	SDL_Renderer* m_mainRenderer;


public:
	TextComponent(std::string fontPath, std::string text, int xCoord, int yCoord, int textWidth, int textHeight, SDL_Renderer* renderer, int fontSize);
	void renderText(SDL_Renderer* renderer, int position);
	void switchColor();
};

