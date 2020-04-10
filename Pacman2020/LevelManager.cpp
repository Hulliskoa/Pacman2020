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

	lvlFile.open("..\\Pacman2020\\levels\\lvl2.txt");
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

	char upTile;
	char rightTile;
	char leftTile;
	char downTile;
	char leftDownTile;
	char rightDownTile;
	char rightUpTile;
	char leftUpTile;

	for (int y = 0; y < 31; y++) {
		for (int x = 0; x < 28; x++) {


			std::shared_ptr<Entity> lvlEntity;
			char currentEntity = levelArray[y][x];

			upTile = (y - 1 > 0) ? levelArray[y - 1][x] : 'x';
			rightTile = (x != 28) ? levelArray[y][x + 1] : 'x';
			downTile = (y != 31) ? levelArray[y + 1][x] : 'x';
			leftTile = (x - 1 > 0) ? levelArray[y][x - 1] : 'x';

			//controll structure for drawing and creating map from textfile
			if (currentEntity == 'x')
			{



				if (downTile == 'x' && leftTile == 'x' && upTile == 'x' && rightTile == 'x') {
					lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
					lvlEntity->startAnimation->addRect(208, 88, 8, 8);
					lvlEntity->setEntityType(EntityType::NOT_DEFINED);
					collisionManager->addEntity(lvlEntity);
				}
				else if ((downTile != 'x' && leftTile == 'x') && (upTile == 'x' && rightTile == 'x')) {
					lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
					lvlEntity->startAnimation->addRect(351, 27, 8, 8);
					lvlEntity->setEntityType(EntityType::WALL);
					collisionManager->addEntity(lvlEntity);

				}
				else if ((downTile == 'x' && leftTile == 'x') && (upTile != 'x' && rightTile == 'x')) {
					lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
					lvlEntity->startAnimation->addRect(270, 36, 8, 8);
					lvlEntity->setEntityType(EntityType::WALL);
					collisionManager->addEntity(lvlEntity);

				}
				else if ((downTile == 'x' && leftTile == 'x') && (upTile != 'x' && rightTile != 'x')) {
					lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
					lvlEntity->startAnimation->addRect(279, 36, 8, 8);
					lvlEntity->setEntityType(EntityType::WALL);
					collisionManager->addEntity(lvlEntity);

				}
				else if ((downTile == 'x' && leftTile != 'x') && (upTile == 'x' && rightTile == 'x')) {
					lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
					lvlEntity->startAnimation->addRect(306, 36, 8, 8);
					lvlEntity->setEntityType(EntityType::WALL);
					collisionManager->addEntity(lvlEntity);

				}
				else if ((downTile == 'x' && leftTile == 'x') && (upTile == 'x' && rightTile != 'x')) {
					lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
					lvlEntity->startAnimation->addRect(297, 36, 8, 8);
					lvlEntity->setEntityType(EntityType::WALL);
					collisionManager->addEntity(lvlEntity);

				}
				else if ((downTile != 'x' && leftTile == 'x') && (upTile == 'x' && rightTile != 'x')) {
					lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
					lvlEntity->startAnimation->addRect(315, 36, 8, 8);
					lvlEntity->setEntityType(EntityType::WALL);
					collisionManager->addEntity(lvlEntity);

				}
				else if ((downTile == 'x' && leftTile != 'x') && (upTile != 'x' && rightTile == 'x')) {
					lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
					lvlEntity->startAnimation->addRect(288, 36, 8, 8);
					lvlEntity->setEntityType(EntityType::WALL);
					collisionManager->addEntity(lvlEntity);

				}else if ((downTile != 'x' && leftTile != 'x') && (upTile == 'x' && rightTile == 'x')) {
					lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
					lvlEntity->startAnimation->addRect(324, 36, 8, 8);
					lvlEntity->setEntityType(EntityType::WALL);
					collisionManager->addEntity(lvlEntity);

				}
				else if (downTile == 'x' && downTile + 1 != 'x' && leftTile == 'x' && upTile == 'x' && rightTile == 'x') {
					lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
						lvlEntity->startAnimation->addRect(288, 36, 8, 8);
						lvlEntity->setEntityType(EntityType::WALL);
						collisionManager->addEntity(lvlEntity);

				}
				else
				{
					lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
						lvlEntity->startAnimation->addRect(208, 88, 8, 8);
						lvlEntity->setEntityType(EntityType::NOT_DEFINED);
					collisionManager->addEntity(lvlEntity);
				}


			}
			else if (currentEntity == 'o')
			{
				lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
				lvlEntity->startAnimation->addRect(342, 72, 8, 8);
				collisionManager->addEntity(lvlEntity);
				lvlEntity->setEntityType(EntityType::PELLET);
			}
			else
			{
				lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
				lvlEntity->startAnimation->addRect(333, 72, 8, 8);
				collisionManager->addEntity(lvlEntity);
				lvlEntity->setEntityType(EntityType::NOT_DEFINED);
			}

			/*

			rightTile = levelArray[y][x];
			if (currentEntity == '-') {
				lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
				lvlEntity->startAnimation->addRect(351, 27, 8, 8);
				lvlEntity->setEntityType(EntityType::WALL);
				collisionManager->addEntity(lvlEntity);

			}
			else if (currentEntity == '|') {
				lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
				lvlEntity->startAnimation->addRect(306, 36, 8, 8);
				lvlEntity->setEntityType(EntityType::WALL);
				collisionManager->addEntity(lvlEntity);

			}
			else if (currentEntity == 'x') {
				lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
				lvlEntity->startAnimation->addRect(333, 72, 8, 8);
				lvlEntity->setEntityType(EntityType::NOT_DEFINED);
				collisionManager->addEntity(lvlEntity);
			}
			else if (currentEntity == 'o') {
				lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
				lvlEntity->startAnimation->addRect(342, 72, 8, 8);
				collisionManager->addEntity(lvlEntity);
				lvlEntity->setEntityType(EntityType::PELLET);
			}
			else if (currentEntity == 'e') {
				lvlEntity = std::make_shared<Entity>(renderer, (x + xOffset) * 8, (y + yOffset) * 8, 1, mazeSprites);
				lvlEntity->startAnimation->addRect(342, 72, 8, 8);
				collisionManager->addEntity(lvlEntity);
				lvlEntity->setEntityType(EntityType::NOT_DEFINED);
			}
			*/
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
			m_textureWidth = mainSpriteSheet->w;
			m_textureHeight = mainSpriteSheet->h;
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
		m_textureWidth = 0;
		m_textureHeight = 0;
	}

}