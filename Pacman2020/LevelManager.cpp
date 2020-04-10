#include "LevelManager.h"

LevelManager::LevelManager(SDL_Renderer* mainRenderer) : renderer(mainRenderer) {
	//mazeSprites = IMG_Load("..\\Pacman2020\\sprites\\mazeParts.png");

	mazeSprites = IMG_Load("..\\Pacman2020\\sprites\\mazeParts.png");
	if (!loadFromFile(mazeSprites))
	{
		std::cout << "Failed to load sprite sheet texture!" << std::endl;

	}
}

LevelManager::~LevelManager()
{
	free();
}

void LevelManager::createLevel(std::shared_ptr<CollisionManager> collisionManager, int currentLvl)
{
	std::ifstream lvlFile;

	lvlFile.open("..\\Pacman2020\\levels\\lvl1.txt");
	char currentChar;
	int rowCounter = 0;
	int columnCounter = 0;

	if (!lvlFile) {
		std::cerr << "Unable to open lvlfile";
		exit(1);
	}
	while (lvlFile >> currentChar) {

		levelArray[rowCounter][columnCounter] = currentChar;
		columnCounter++;

		if (columnCounter >= 28) {
			columnCounter = 0;
			rowCounter++;

		}
	}



	for (int y = 4; y < 35; y++) {
		for (int x = 3; x < 31; x++) {
			std::shared_ptr<Entity> lvlEntity;
			char currentEntity = levelArray[y - 4][x - 3];

			if (currentEntity == '-') {
				lvlEntity = std::make_shared<Entity>(renderer, x * 8, y * 8, 1, mazeSprites);
				lvlEntity->startAnimation->addRect(351, 27, 8, 8);
				lvlEntity->setEntityType(EntityType::WALL);
				collisionManager->addEntity(lvlEntity);

			}
			else if (currentEntity == '|') {
				lvlEntity = std::make_shared<Entity>(renderer, x * 8, y * 8, 1, mazeSprites);
				lvlEntity->startAnimation->addRect(306, 36, 8, 8);
				lvlEntity->setEntityType(EntityType::WALL);
				collisionManager->addEntity(lvlEntity);

			}
			else if (currentEntity == 'x') {
				lvlEntity = std::make_shared<Entity>(renderer, x * 8, y * 8, 1, mazeSprites);
				lvlEntity->startAnimation->addRect(333, 72, 8, 8);
				lvlEntity->setEntityType(EntityType::NOT_DEFINED);
				collisionManager->addEntity(lvlEntity);
			}
			else if (currentEntity == 'o') {
				lvlEntity = std::make_shared<Entity>(renderer, x * 8, y * 8, 1, mazeSprites);
				lvlEntity->startAnimation->addRect(342, 72, 8, 8);
				collisionManager->addEntity(lvlEntity);
				lvlEntity->setEntityType(EntityType::PELLET);
			}
			entityArray.emplace_back(lvlEntity);
		}
	}

}

bool LevelManager::loadFromFile(SDL_Surface* mainSpriteSheet)
{
	free();
	SDL_Texture* newTexture = NULL;

	if (mainSpriteSheet == NULL)
	{
		std::cout << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		SDL_SetColorKey(mainSpriteSheet, SDL_TRUE, SDL_MapRGB(mainSpriteSheet->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, mainSpriteSheet);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			m_width = mainSpriteSheet->w;
			m_height = mainSpriteSheet->h;
		}
	}
	m_texture = newTexture;
	return m_texture != NULL;
}


void LevelManager::renderLevel()
{
	for (auto xX : entityArray) {
		if (xX->getEntityType() != EntityType::NOT_DEFINED)
			xX->startAnimation->render(xX->coordinates[0], xX->coordinates[1]);

	}
}

void LevelManager::free()
{
	if (m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_width = 0;
		m_height = 0;
	}

}