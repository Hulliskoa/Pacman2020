#include "Score.h"

Score::Score(SDL_Renderer* renderer) : gameRenderer(renderer)
{
	loadspriteSheetTexture("..\\Pacman2020\\sprites\\spriteFont.png");
	zero = std::make_shared<AnimationComponent>(10, m_scoreTexture, m_textureWidth, m_textureHeight);
	one = std::make_shared<AnimationComponent>(10, m_scoreTexture, m_textureWidth, m_textureHeight);
	two = std::make_shared<AnimationComponent>(10, m_scoreTexture, m_textureWidth, m_textureHeight);
	three = std::make_shared<AnimationComponent>(10, m_scoreTexture, m_textureWidth, m_textureHeight);
	four = std::make_shared<AnimationComponent>(10, m_scoreTexture, m_textureWidth, m_textureHeight);
	five = std::make_shared<AnimationComponent>(10, m_scoreTexture, m_textureWidth, m_textureHeight);
	six = std::make_shared<AnimationComponent>(10, m_scoreTexture, m_textureWidth, m_textureHeight);
	seven = std::make_shared<AnimationComponent>(10, m_scoreTexture, m_textureWidth, m_textureHeight);
	eight = std::make_shared<AnimationComponent>(10, m_scoreTexture, m_textureWidth, m_textureHeight);
	nine = std::make_shared<AnimationComponent>(10, m_scoreTexture, m_textureWidth, m_textureHeight);

	zero->addRect(1, 1, 47, 47);
	zero->addRect(49, 1, 47, 47);
	zero->addRect(97, 1, 47, 47);
	zero->addRect(145, 1, 47, 47);
	zero->addRect(193, 1, 47, 47);
	zero->addRect(241, 1, 47, 47);
	zero->addRect(289, 1, 47, 47);
	zero->addRect(337, 1, 47, 47);
	zero->addRect(385, 1, 47, 47);
	zero->addRect(433, 1, 47, 47);

	one->addRect(1, 1, 47, 47);
	one->addRect(49, 1, 47, 47);
	one->addRect(97, 1, 47, 47);
	one->addRect(145, 1, 47, 47);
	one->addRect(193, 1, 47, 47);
	one->addRect(241, 1, 47, 47);
	one->addRect(289, 1, 47, 47);
	one->addRect(337, 1, 47, 47);
	one->addRect(385, 1, 47, 47);
	one->addRect(433, 1, 47, 47);

	two->addRect(1, 1, 47, 47);
	two->addRect(49, 1, 47, 47);
	two->addRect(97, 1, 47, 47);
	two->addRect(145, 1, 47, 47);
	two->addRect(193, 1, 47, 47);
	two->addRect(241, 1, 47, 47);
	two->addRect(289, 1, 47, 47);
	two->addRect(337, 1, 47, 47);
	two->addRect(385, 1, 47, 47);
	two->addRect(433, 1, 47, 47);

	three->addRect(1, 1, 47, 47);
	three->addRect(49, 1, 47, 47);
	three->addRect(97, 1, 47, 47);
	three->addRect(145, 1, 47, 47);
	three->addRect(193, 1, 47, 47);
	three->addRect(241, 1, 47, 47);
	three->addRect(289, 1, 47, 47);
	three->addRect(337, 1, 47, 47);
	three->addRect(385, 1, 47, 47);
	three->addRect(433, 1, 47, 47);

	four->addRect(1, 1, 47, 47);
	four->addRect(49, 1, 47, 47);
	four->addRect(97, 1, 47, 47);
	four->addRect(145, 1, 47, 47);
	four->addRect(193, 1, 47, 47);
	four->addRect(241, 1, 47, 47);
	four->addRect(289, 1, 47, 47);
	four->addRect(337, 1, 47, 47);
	four->addRect(385, 1, 47, 47);
	four->addRect(433, 1, 47, 47);

	five->addRect(1, 1, 47, 47);
	five->addRect(49, 1, 47, 47);
	five->addRect(97, 1, 47, 47);
	five->addRect(145, 1, 47, 47);
	five->addRect(193, 1, 47, 47);
	five->addRect(241, 1, 47, 47);
	five->addRect(289, 1, 47, 47);
	five->addRect(337, 1, 47, 47);
	five->addRect(385, 1, 47, 47);
	five->addRect(433, 1, 47, 47);

	six->addRect(1, 1, 47, 47);
	six->addRect(49, 1, 47, 47);
	six->addRect(97, 1, 47, 47);
	six->addRect(145, 1, 47, 47);
	six->addRect(193, 1, 47, 47);
	six->addRect(241, 1, 47, 47);
	six->addRect(289, 1, 47, 47);
	six->addRect(337, 1, 47, 47);
	six->addRect(385, 1, 47, 47);
	six->addRect(433, 1, 47, 47);

	seven->addRect(1, 1, 47, 47);
	seven->addRect(49, 1, 47, 47);
	seven->addRect(97, 1, 47, 47);
	seven->addRect(145, 1, 47, 47);
	seven->addRect(193, 1, 47, 47);
	seven->addRect(241, 1, 47, 47);
	seven->addRect(289, 1, 47, 47);
	seven->addRect(337, 1, 47, 47);
	seven->addRect(385, 1, 47, 47);
	seven->addRect(433, 1, 47, 47);

	eight->addRect(1, 1, 47, 47);
	eight->addRect(49, 1, 47, 47);
	eight->addRect(97, 1, 47, 47);
	eight->addRect(145, 1, 47, 47);
	eight->addRect(193, 1, 47, 47);
	eight->addRect(241, 1, 47, 47);
	eight->addRect(289, 1, 47, 47);
	eight->addRect(337, 1, 47, 47);
	eight->addRect(385, 1, 47, 47);
	eight->addRect(433, 1, 47, 47);

	nine->addRect(1, 1, 47, 47);
	nine->addRect(49, 1, 47, 47);
	nine->addRect(97, 1, 47, 47);
	nine->addRect(145, 1, 47, 47);
	nine->addRect(193, 1, 47, 47);
	nine->addRect(241, 1, 47, 47);
	nine->addRect(289, 1, 47, 47);
	nine->addRect(337, 1, 47, 47);
	nine->addRect(385, 1, 47, 47);
	nine->addRect(433, 1, 47, 47);
}

void Score::update(std::shared_ptr<Pacman> pacman)
{

	int score = pacman->getScore();

	int positionZero = score % 10;
	int positionOne = score / 10 % 10;
	int positionTwo = score / 100 % 10;
	int positionThree = score / 1000 % 10;
	int positionFour = score / 10000 % 10;
	int positionFive = score / 100000 % 10;
	int positionSix = score / 1000000 % 10;
	int positionSeven = score / 10000000 % 10;
	int positionEight = score / 100000000 % 10;
	int positionNine = score / 1000000000 % 10;

	zero->renderSpriteFonts(82, 1, gameRenderer, positionZero);
	one->renderSpriteFonts(73, 1, gameRenderer, positionOne);
	two->renderSpriteFonts(64, 1, gameRenderer, positionTwo);
	three->renderSpriteFonts(55, 1, gameRenderer, positionThree);
	four->renderSpriteFonts(46, 1, gameRenderer, positionFour);
	five->renderSpriteFonts(37, 1, gameRenderer, positionFive);
	six->renderSpriteFonts(28, 1, gameRenderer, positionSix);
	seven->renderSpriteFonts(19, 1, gameRenderer, positionSeven);
	eight->renderSpriteFonts(10, 1, gameRenderer, positionEight);
	nine->renderSpriteFonts(1, 1, gameRenderer, positionNine);

}

//source: http://lazyfoo.net/tutorials/SDL/07_texture_loading_and_rendering/index.php
bool Score::loadspriteSheetTexture(std::string path)
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
		newTexture = SDL_CreateTextureFromSurface(gameRenderer, loadedSurface);
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
	m_scoreTexture = newTexture;
	return m_scoreTexture != NULL;
}