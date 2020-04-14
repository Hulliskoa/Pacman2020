#include "LevelManager.h"

LevelManager::LevelManager(SDL_Renderer* mainRenderer) : renderer(mainRenderer) {
	//mazeSprites = IMG_Load("..\\Pacman2020\\sprites\\mazeParts.png");


	if (!loadspriteSheetTexture("..\\Pacman2020\\sprites\\mazeParts.png")) {
		std::cout << "could not load maze spritesheet" << std::endl;
	}
}

LevelManager::~LevelManager()
{
	if (m_levelSpriteSheet != NULL)
	{
		SDL_DestroyTexture(m_levelSpriteSheet);
		m_levelSpriteSheet = NULL;
		m_textureWidth = 0;
		m_textureHeight = 0;
	}
}

bool LevelManager::readLevelFromTxt(int currentLvl) {
	std::ifstream lvlFile;
	std::string path ="..\\Pacman2020\\levels\\lvl" +std::to_string(currentLvl) + ".txt";

	lvlFile.open(path);
	char currentChar;
	int rowCounter = 0;
	int columnCounter = 0;

	if (!lvlFile) {
		std::cerr << "Unable to open lvlfile";
		return false;
	}
	while (lvlFile >> currentChar) {

		levelArray[rowCounter][columnCounter] = currentChar;
		columnCounter++;

		if (columnCounter >= 28) {
			columnCounter = 0;
			rowCounter++;

		}
	}
	return true;
}

void LevelManager::createLevel(std::shared_ptr<CollisionManager> collisionManager)
{
	//entityArray.clear();
	char upTile;
	char rightTile;
	char leftTile;
	char downTile;
	//char leftDownTile;
	//char rightDownTile;
	//char rightUpTile;
	//char leftUpTile;

	int xCoord = 0;
	int yCoord = 0;
	EntityType entityType = EntityType::NOT_DEFINED;

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
					xCoord = 288;
					yCoord = 88;
					entityType = EntityType::NOT_DEFINED;
				}
				else if ((downTile != 'x' && leftTile == 'x') && (upTile == 'x' && rightTile == 'x')) {
					xCoord = 351;
					yCoord = 27;
					entityType = EntityType::WALL;
				}
				else if ((downTile == 'x' && leftTile == 'x') && (upTile != 'x' && rightTile == 'x')) {
					xCoord = 270;
					yCoord = 36;
					entityType = EntityType::WALL;

				}
				else if ((downTile == 'x' && leftTile == 'x') && (upTile != 'x' && rightTile != 'x')) {
					xCoord = 279;
					yCoord = 36;
					entityType = EntityType::WALL;

				}
				else if ((downTile == 'x' && leftTile != 'x') && (upTile == 'x' && rightTile == 'x')) {
					xCoord = 306;
					yCoord = 36;
					entityType = EntityType::WALL;

				}
				else if ((downTile == 'x' && leftTile == 'x') && (upTile == 'x' && rightTile != 'x')) {

					xCoord = 297;
					yCoord = 36;
					entityType = EntityType::WALL;

				}
				else if ((downTile != 'x' && leftTile == 'x') && (upTile == 'x' && rightTile != 'x')) {
					xCoord = 315;
					yCoord = 36;
					entityType = EntityType::WALL;


				}
				else if ((downTile == 'x' && leftTile != 'x') && (upTile != 'x' && rightTile == 'x')) {
					xCoord = 288;
					yCoord = 36;
					entityType = EntityType::WALL;
				}
				else if ((downTile != 'x' && leftTile != 'x') && (upTile == 'x' && rightTile == 'x')) {
					xCoord = 324;
					yCoord = 36;
					entityType = EntityType::WALL;
				}
				else if (downTile == 'x' && downTile + 1 != 'x' && leftTile == 'x' && upTile == 'x' && rightTile == 'x') {
					xCoord = 288;
					yCoord = 36;
					entityType = EntityType::WALL;
				}
				else
				{
					xCoord = 208;
					yCoord = 88;
					entityType = EntityType::NOT_DEFINED;

				}
			}
			else if (currentEntity == 'o')
			{
				xCoord = 342;
				yCoord = 72;
				entityType = EntityType::PELLET;
			}
			else if (currentEntity == 'B' && (y - 1 < 0 || levelArray[y - 1][x] == 'e')) {
				xCoord = 315;
				yCoord = 27;
				entityType = EntityType::WALL;

			}
			else if (currentEntity == 'B' && (y + 1 > 30 || levelArray[y + 1][x] == 'e')) {
				xCoord = 333;
				yCoord = 27;
				entityType = EntityType::WALL;
			}
			else if (currentEntity == 'B' && (x - 1 < 0 || levelArray[y][x - 1] == 'e')) {
				xCoord = 252;
				yCoord = 27;
				entityType = EntityType::WALL;
			}
			else if (currentEntity == 'B' && (x + 1 > 27 || levelArray[y][x + 1] == 'e')) {
				xCoord = 243;
				yCoord = 27;
				entityType = EntityType::WALL;
			}
			else if (currentEntity == '0') {
				xCoord = 225;
				yCoord = 27;
				entityType = EntityType::WALL;
			}
			else if (currentEntity == '1') {
				xCoord = 261;
				yCoord = 27;
				entityType = EntityType::WALL;
			}
			else if (currentEntity == '2') {
				xCoord = 288;
				yCoord = 45;
				entityType = EntityType::WALL;
			}
			else if (currentEntity == '3') {
				xCoord = 324;
				yCoord = 36;
				entityType = EntityType::WALL;
			}
			else if (currentEntity == '4') {
				xCoord = 270;
				yCoord = 27;
				entityType = EntityType::WALL;

			}
			else if (currentEntity == '5') {
				xCoord = 234;
				yCoord = 27;
				entityType = EntityType::WALL;
			}
			else if (currentEntity == '6') {
				xCoord = 315;
				yCoord = 36;
				entityType = EntityType::WALL;
			}
			else if (currentEntity == '7') {
				xCoord = 279;
				yCoord = 36;
				entityType = EntityType::WALL;

			}
			else if (currentEntity == '8') {
				xCoord = 324;
				yCoord = 45;
				entityType = EntityType::WALL;

			}
			else if (currentEntity == '9') {
				xCoord = 315;
				yCoord = 45;
				entityType = EntityType::WALL;

			}
			else if (currentEntity == 'W') {
				xCoord = 279;
				yCoord = 27;
				entityType = EntityType::WALL;
			}
			else if (currentEntity == 'X') {
				xCoord = 297;
				yCoord = 27;
				entityType = EntityType::WALL;
			}
			else if (currentEntity == 'Y') {
				xCoord = 306;
				yCoord = 27;
				entityType = EntityType::WALL;

			}
			else if (currentEntity == 'Z') {
				xCoord = 288;
				yCoord = 27;
				entityType = EntityType::WALL;

			}
			else if (currentEntity == 'O') {
				xCoord = 360;
				yCoord = 45;
				entityType = EntityType::POWER_PELLET;
			}
			else
			{
				xCoord = 333;
				yCoord = 72;
				entityType = EntityType::NOT_DEFINED;
			}

			lvlEntity = std::make_shared<Entity>((x + xMapOffset) * 8, (y + yMapOffset) * 8, 1, m_levelSpriteSheet, m_textureWidth, m_textureHeight);
			lvlEntity->startAnimation->addRect(xCoord, yCoord, 8, 8);
			lvlEntity->setEntityType(entityType);
			collisionManager->addEntity(lvlEntity);
			entityArray.emplace_back(lvlEntity);
		}
	}

}


void LevelManager::renderLevel(SDL_Renderer* renderer)
{
	for (auto x : entityArray) {
		if (x->getEntityType() != EntityType::NOT_DEFINED)
			x->startAnimation->render(x->coordinates[0], x->coordinates[1], renderer);

	}
}

bool LevelManager::loadspriteSheetTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
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
	m_levelSpriteSheet = newTexture;
	return m_levelSpriteSheet != NULL;
}
