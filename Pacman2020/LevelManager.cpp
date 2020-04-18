#include "LevelManager.h"

LevelManager::LevelManager(SDL_Renderer* mainRenderer) : renderer(mainRenderer) {



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


	std::string path = "..\\Pacman2020\\levels\\lvl" + std::to_string(currentLvl) + ".txt";
	lvlFile.open(path);
	char currentChar;
	int rowCounter = 0;
	int columnCounter = 0;

	if (!lvlFile) {
		std::cerr << "Unable to open lvlfile" << std::endl;
		lvlFile.clear();
		lvlFile.close();
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

	lvlFile.clear();
	lvlFile.close();
	return true;
}
void LevelManager::createLevel(std::shared_ptr<CollisionManager> collisionManager)
{

	if (!loadspriteSheetTexture("..\\Pacman2020\\sprites\\mazeParts.png")) {
		std::cout << "could not load maze spritesheet" << std::endl;
	}

	if (!readLevelFromTxt(currentMap)) {
		std::cout << "could not open lvlfile" << std::endl;
	}


	entityArray.clear();
	entityArray.shrink_to_fit();
	ghostDoors.erase(ghostDoors.begin(), ghostDoors.end());
	ghostDoors.shrink_to_fit();

	char upTile = 0;
	char rightTile = 0;
	char leftTile = 0;
	char downTile = 0;
	char leftDownTile = 0;
	char rightDownTile = 0;
	char rightUpTile = 0;
	char leftUpTile = 0;

	int xCoord = 0;//spritesheet coordinates
	int yCoord = 0;//spritesheet coordinates
	EntityType entityType;

	for (int y = 0; y < 31; y++) {
		for (int x = 0; x < 28; x++) {
			entityType = EntityType::NOT_DEFINED;
			std::shared_ptr<Entity> lvlEntity;
			char currentTile = levelArray[y][x];

			//checks each tile around current tile to be used later
			rightTile = (x + 1 > 27) ? 's' : levelArray[y][x + 1];
			leftTile = (x - 1 < 0) ? 's' : levelArray[y][x - 1];
			upTile = (y - 1 < 0) ? 's' : levelArray[y - 1][x];
			downTile = (y + 1 > 30) ? 's' : levelArray[y + 1][x];

			rightDownTile = (y + 1 > 30 || x + 1 > 27) ? 's' : levelArray[y + 1][x + 1];
			leftUpTile = (y - 1 < 0 || x - 1 < 0) ? 's' : levelArray[y - 1][x - 1];
			rightUpTile = (y - 1 < 0 || x + 1 > 27) ? 's' : levelArray[y - 1][x + 1];
			leftDownTile = (y + 1 > 30 || x - 1 < 0) ? 's' : levelArray[y + 1][x - 1];

			//Special outer borders
			if (currentTile == 'B') {
				//Outer border
				entityType = EntityType::WALL;

				//left side down corners
				if (downTile == 'B' && rightTile == 'x' && upTile == 'B') {
					xCoord = 234;
					yCoord = 27;
				}

				if (downTile == 'B' && rightTile == 'B' && upTile == 's') {
					xCoord = 234;
					yCoord = 27;
				}
				else if (downTile == 'B' && rightTile == 'B' && upTile != 's') {
					xCoord = 288;
					yCoord = 36;
				}

				//Right side down corners
				else if (downTile == 'B' && leftTile == 'B' && upTile == 's') {
					xCoord = 225;
					yCoord = 27;
				}
				else if (downTile == 'B' && leftTile == 'B' && upTile != 's') {
					xCoord = 279;
					yCoord = 36;
				}

				//right side up corners
				else if (upTile == 'B' && leftTile == 'B' && rightTile == 's') {
					xCoord = 261;
					yCoord = 27;
				}
				else if (upTile == 'B' && leftTile == 'B' && rightTile != 's') {
					xCoord = 315;
					yCoord = 36;
				}

				//left side up corners
				else if (upTile == 'B' && rightTile == 'B' && leftTile == 's') {
					xCoord = 270;
					yCoord = 27;
				}
				else if (upTile == 'B' && rightTile == 'B' && leftTile != 's') {
					xCoord = 324;
					yCoord = 36;
				}

				//bottom border
				else if (downTile == 's' && (leftTile != 's' || rightTile != 's')) {
					xCoord = 333;
					yCoord = 27;
				}

				//top border
				else if (upTile == 's' && (leftTile != 's' || rightTile != 's')) {
					xCoord = 315;
					yCoord = 27;
				}

				//left border
				else if (leftTile == 's') {
					xCoord = 252;
					yCoord = 27;
				}

				//right border
				else if (rightTile == 's') {
					xCoord = 243;
					yCoord = 27;
				}
			}
			//Special outer borders with curve and straight wall
			else if (currentTile == 'C')
			{
				entityType = EntityType::WALL;
				if (rightTile == 's' && upTile == 'C') {
					xCoord = 297;
					yCoord = 27;

				}
				else if (rightTile == 's' && downTile == 'C') {
					xCoord = 279;
					yCoord = 27;

				}
				else if (leftTile == 's' && downTile == 'C') {
					xCoord = 288;
					yCoord = 27;

				}
				else if (leftTile == 's' && upTile == 'C') {
					xCoord = 306;
					yCoord = 27;

				}
				else if (upTile == 's' && leftTile == 'C') {
					xCoord = 315;
					yCoord = 45;

				}
				else if (upTile == 's' && rightTile == 'C') {
					xCoord = 324;
					yCoord = 45;

				}
			}
			//Ghost cage
			else if (currentTile == 'G')
			{
				entityType = EntityType::WALL;
				//left side lower corner
				if (rightTile == 'G' && upTile == 'G') {
					xCoord = 360;
					yCoord = 36;
				}
				//left side upper corner
				else if (rightTile == 'G' && downTile == 'G') {
					xCoord = 342;
					yCoord = 36;
				}
				//right side upper corner
				else if (leftTile == 'G' && downTile == 'G') {
					xCoord = 333;
					yCoord = 36;
				}
				//right side lower corner
				else if (leftTile == 'G' && upTile == 'G') {
					xCoord = 351;
					yCoord = 36;
				}
				//horizontal walls right side of door
				else if (rightTile == 'G' && leftTile == 'D') {
					xCoord = 225;
					yCoord = 45;
				}
				else if (rightTile == 'G' && leftTile == 'G' || leftTile == 'D') {
					if (y > 15) {
						xCoord = 324;
						yCoord = 27;
					}
					else {
						xCoord = 333;
						yCoord = 27;
					}
				}
				//horizontal walls left side of door
				else if (leftTile == 'G' && rightTile == 'D') {
					xCoord = 234;
					yCoord = 45;

				}
				else if (leftTile == 'G' && rightTile == 'G' || rightTile == 'D') {
					if (y > 15) {
						xCoord = 324;
						yCoord = 27;
					}
					else {
						xCoord = 333;
						yCoord = 27;
					}
				}
				//vertical walls
				else if (upTile == 'G' && downTile == 'G') {
					if (x > 14) {
						xCoord = 252;
						yCoord = 27;
					}
					else {
						xCoord = 243;
						yCoord = 27;
					}

				}
			}
			//door in ghost cage
			else if (currentTile == 'D')
			{
				entityType = EntityType::DOOR;
				xCoord = 104;
				yCoord = 96;

			}
			//maze parts inside borders
			else if (currentTile == 'x')
			{
				entityType = EntityType::WALL;
				//Transition between border walls and inner maze walls
				if ((leftTile == 'C' || rightTile == 'C') && upTile != 'x') {
					xCoord = 351;
					yCoord = 27;
				}
				else if ((leftTile == 'C' || rightTile == 'C') && downTile != 'x') {
					xCoord = 270;
					yCoord = 36;
				}
				else if ((upTile == 'C' || downTile == 'C') && rightTile != 'x') {
					xCoord = 297;
					yCoord = 36;

				}
				else if ((upTile == 'C' || downTile == 'C') && leftTile != 'x') {
					xCoord = 306;
					yCoord = 36;

				}
				else if (upTile != 'x' && leftTile != 'x' && downTile == 'x' && rightTile == 'x') {
					xCoord = 288;
					yCoord = 45;
				}
				else if (upTile != 'x' && leftTile == 'x' && downTile == 'x' && rightTile != 'x') {
					xCoord = 279;
					yCoord = 36;
				}
				else if (upTile == 'x' && leftTile == 'x' && downTile != 'x' && rightTile != 'x') {
					xCoord = 315;
					yCoord = 36;
				}
				else if (upTile == 'x' && leftTile != 'x' && downTile != 'x' && rightTile == 'x') {
					xCoord = 324;
					yCoord = 36;
				}
				else if (upTile != 'x' && leftTile == 'x' && downTile == 'x' && rightTile == 'x') {
					xCoord = 351;
					yCoord = 27;
				}
				else if (upTile == 'x' && leftTile == 'x' && downTile != 'x' && rightTile == 'x') {
					xCoord = 270;
					yCoord = 36;
				}
				else if (upTile == 'x' && leftTile == 'x' && downTile == 'x' && rightTile != 'x') {
					xCoord = 297;
					yCoord = 36;
				}
				else if (upTile == 'x' && leftTile != 'x' && downTile == 'x' && rightTile == 'x') {
					xCoord = 306;
					yCoord = 36;
				}
				else if (rightUpTile != 'x' && leftUpTile == 'x' && rightDownTile == 'x' && leftDownTile == 'x') {
					xCoord = 261;
					yCoord = 45;
				}
				else if (rightUpTile == 'x' && leftUpTile != 'x' && rightDownTile == 'x' && leftDownTile == 'x') {
					xCoord = 270;
					yCoord = 45;
				}
				else if (rightUpTile == 'x' && leftUpTile == 'x' && rightDownTile != 'x' && leftDownTile == 'x') {
					xCoord = 243;
					yCoord = 45;
				}
				else if (rightUpTile == 'x' && leftUpTile == 'x' && rightDownTile == 'x' && leftDownTile != 'x') {
					xCoord = 252;
					yCoord = 45;
				}
			}
			//Pellets and empty space inside maze
			else {
				if (currentTile == 'o') {
					xCoord = 342;
					yCoord = 72;
					entityType = EntityType::PELLET;
				}
				else if (currentTile == 'O') {
					xCoord = 360;
					yCoord = 45;
					entityType = EntityType::POWER_PELLET;
				}
				else if (currentTile == 'F') {
					xCoord = 360;
					yCoord = 45;
					entityType = EntityType::NOT_DEFINED;
				}

			}
			if (currentTile != 's') {
				lvlEntity = std::make_shared<Entity>((x + xMapOffset) * 8, (y + yMapOffset) * 8, 1, m_levelSpriteSheet, m_textureWidth, m_textureHeight);
				entityArray.emplace_back(lvlEntity);
				lvlEntity->startAnimation->addRect(xCoord, yCoord, 8, 8);
				lvlEntity->setEntityType(entityType);
				collisionManager->addEntity(lvlEntity);
				if (entityType == EntityType::DOOR) {
					ghostDoors.emplace_back(lvlEntity);
				}
			}
			xCoord = 208;
			yCoord = 88;
		}
	}


	currentLvl++;
	currentMap++;
	if (currentMap > 3) {
		currentMap = 1;
	}
}
void LevelManager::renderLevel(SDL_Renderer* gameRenderer)
{
	int counter = 0;
	for (auto x : entityArray) {

		if (x->getEntityType() != EntityType::NOT_DEFINED && x->getEntityType() != EntityType::INTERSECTION && x->getEntityType() != EntityType::INACTIVE_PELLET && x->getEntityType() != EntityType::INACTIVE_POWER_PELLET) {
			x->startAnimation->render(x->coordinates[0], x->coordinates[1], gameRenderer, 0);
			counter++;
		}

	}
	//std::cout << counter << std::endl;
}
void LevelManager::createInterSections(std::shared_ptr<CollisionManager> collisionManager)
{
	char upTile = 0;
	char rightTile = 0;
	char leftTile = 0;
	char downTile = 0;
	int countTiles = 0;
	EntityType entityType = EntityType::INTERSECTION;
	for (int y = 0; y < 31; y++) {
		for (int x = 0; x < 28; x++) {
			char currentTile = levelArray[y][x];
			upTile = (y - 1 > 0) ? levelArray[y - 1][x] : 'x';
			rightTile = (x != 28) ? levelArray[y][x + 1] : 'x';
			downTile = (y != 31) ? levelArray[y + 1][x] : 'x';
			leftTile = (x - 1 > 0) ? levelArray[y][x - 1] : 'x';

			if (currentTile == 'o' || currentTile == 'O' || currentTile == 'F') {
				if (upTile == 'o' || upTile == 'O' || upTile == 'F')
					countTiles++;
				if (leftTile == 'o' || leftTile == 'O' || leftTile == 'F')
					countTiles++;
				if (rightTile == 'o' || rightTile == 'O' || rightTile == 'F')
					countTiles++;
				if (downTile == 'o' || downTile == 'O' || downTile == 'F')
					countTiles++;
				if ((downTile == 'x' || downTile == 'B' || downTile == 'G') && (upTile == 'x' || upTile == 'B' || upTile == 'G'))
					countTiles--;
				if ((leftTile == 'x' || leftTile == 'B' || leftTile == 'G') && (rightTile == 'x' || rightTile == 'B' || rightTile == 'G'))
					countTiles--;

				if (countTiles >= 2) {
					std::shared_ptr<Entity> lvlEntity;
					lvlEntity = std::make_shared<Entity>((x + xMapOffset) * 8, (y + yMapOffset) * 8, 1, m_levelSpriteSheet, m_textureWidth, m_textureHeight);
					lvlEntity->startAnimation->addRect(192, 88, 8, 8);
					lvlEntity->setEntityType(entityType);
					collisionManager->addEntity(lvlEntity);
					entityArray.emplace_back(lvlEntity);
					if (entityType == EntityType::DOOR) {
						ghostDoors.emplace_back(lvlEntity);
					}
				}
			}
			countTiles = 0;
		}
	}
}
bool LevelManager::loadspriteSheetTexture(std::string path)
{
	//The final texture

	if (m_levelSpriteSheet != NULL)
	{

		SDL_DestroyTexture(m_levelSpriteSheet);
		m_levelSpriteSheet = NULL;
		m_textureWidth = 0;
		m_textureHeight = 0;
	}

	SDL_Texture* newTexture = nullptr;

	//Load image at specified path

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		std::cout << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr)
		{
			std::cout << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			m_textureWidth = loadedSurface->w;
			m_textureHeight = loadedSurface->h;
		}
	}
	m_levelSpriteSheet = newTexture;
	//SDL_FreeSurface(loadedSurface);
	return m_levelSpriteSheet != NULL;
}
int LevelManager::pelletCount() {
	int counter = 0;
	for (auto x : entityArray) {
		if (x->getEntityType() == EntityType::PELLET || x->getEntityType() == EntityType::POWER_PELLET) {
			counter++;
		}
	}
	return counter;
}
int LevelManager::getStartingPelletCount()
{
	return startingPelletCount;
}
void LevelManager::openDoors()
{
	for (auto x : ghostDoors) {
		x->setEntityType(EntityType::NOT_DEFINED);
	}
}
void LevelManager::closeDoors()
{
	for (auto x : ghostDoors) {
		x->setEntityType(EntityType::DOOR);
	}
}

int LevelManager::getCurrentLevel()
{
	return currentLvl;
}

void LevelManager::resetLevels()
{
	currentLvl = 1;
	currentMap = 1;
}
