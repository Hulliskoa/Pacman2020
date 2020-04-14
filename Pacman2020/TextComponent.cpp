#include "TextComponent.h"

//https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2

TextComponent::TextComponent(std::string fontPath, std::string text, int xCoord, int yCoord, SDL_Renderer* renderer) : m_text(text), m_mainRenderer(renderer)
{
	TTF_Font* m_font = TTF_OpenFont(fontPath.c_str(), 15);
	color = { 255,255,255 };
	SDL_Surface* m_surfaceMessage1 = TTF_RenderText_Solid(m_font, m_text.c_str(), color);
	color = { 201, 34, 149 };
	SDL_Surface* m_surfaceMessage2 = TTF_RenderText_Solid(m_font, m_text.c_str(), color);
	SDL_Texture* m_message1 = SDL_CreateTextureFromSurface(m_mainRenderer, m_surfaceMessage1);
	SDL_Texture* m_message2 = SDL_CreateTextureFromSurface(m_mainRenderer, m_surfaceMessage2);


	texts.emplace_back(m_message1);
	texts.emplace_back(m_message2);



	message_rect.x = xCoord;  
	message_rect.y = yCoord; 
	message_rect.w = 200; 
	message_rect.h = 50; 


}


void TextComponent::renderText(SDL_Renderer* renderer, int position)
{
	SDL_RenderCopy(renderer, texts[position], NULL, &message_rect);
}

void TextComponent::switchColor()
{
}


