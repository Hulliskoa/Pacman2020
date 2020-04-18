#include "HPComponent.h"

HPComponent::HPComponent(SDL_Renderer* mainRenderer) : renderer(mainRenderer)
{
	loadspriteSheetTexture("..\\Pacman2020\\sprites\\spriteFont.png");
	m_firstLife = std::make_shared<AnimationComponent>(1, m_hpTexture, m_textureWidth, m_textureHeight);
	m_secondLife = std::make_shared<AnimationComponent>(1, m_hpTexture, m_textureWidth, m_textureHeight);
	m_thirdLife = std::make_shared<AnimationComponent>(1, m_hpTexture, m_textureWidth, m_textureHeight);

	m_firstLife->addRect(1, 289, 95, 95);
	m_secondLife->addRect(1, 289, 95, 95);
	m_thirdLife->addRect(1, 289, 95, 95);
}

void HPComponent::update(int life)
{
	if (life == 3) {
		m_firstLife->renderSpriteFonts(30, 280, renderer, 0);
		m_secondLife->renderSpriteFonts(20, 280, renderer, 0);
		m_thirdLife->renderSpriteFonts(10, 280, renderer, 0);
	}
	else if (life == 2) {
		m_secondLife->renderSpriteFonts(20, 280, renderer, 0);
		m_thirdLife->renderSpriteFonts(10, 280, renderer, 0);
	}
	else if (life == 1) {
		m_thirdLife->renderSpriteFonts(10, 280, renderer, 0);
	}
	else {

	}
}

bool HPComponent::loadspriteSheetTexture(std::string path)
{

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		//Color keying black to make the background transparent when rendering sprites
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			m_textureWidth = loadedSurface->w;
			m_textureHeight = loadedSurface->h;
		}
	}
	m_hpTexture = newTexture;
	return m_hpTexture != NULL;
}
