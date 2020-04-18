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
	TTF_Font* m_font = nullptr;
	SDL_Rect message_rect;
	SDL_Color color;
	std::string m_text;
	SDL_Renderer* m_mainRenderer;


public:
	/**
		Constructor
		\param fontPath channel to play sound on (0 or 1);
		\param text -1 loops, 0 plays once, 1 plays twice
		\param xCoord x coordinate text is rendered at
		\param yCoord y coordinate text is rendered at
		\param textWidth widht of textbox
		\param textHeight heigt of textbox
		\param renderer main renderer used for rendering text to screen
		\param fontSize size of font
	*/
	TextComponent(std::string fontPath, std::string text, int xCoord, int yCoord, int textWidth, int textHeight, SDL_Renderer* renderer, int fontSize);

	/**
	Renderes text to screen
		\param position position of the text we want to render i tne texts vector
	*/
	void renderText(int position);
};