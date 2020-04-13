#pragma once
#include <vector>
#include "MovingEntity.h"
#include <SDL.h>
#include <fstream>
#include <iostream>
#include "CollisionManager.h"

/**
	LevelManager renders and creates each level from .txt files containing ascii drawings of the level to be rendered.
	All stationary objects on the level is created and rendered by this class. 
*/
class LevelManager
{
private:
	char levelArray[31][28] = {};
	std::vector<std::shared_ptr<Entity>> entityArray;
	std::vector<std::string> levels;
	SDL_Renderer* renderer;
	SDL_Texture* m_levelSpriteSheet = nullptr;
	int m_textureWidth = 0;
	int m_textureHeight = 0;
	int xMapOffset = 3;
	int yMapOffset = 4;

public:
	LevelManager(SDL_Renderer* mainRenderer);
	~LevelManager();
	void free();
	bool readLevelFromTxt(int currentLvl);
	bool loadspriteSheetTexture(std::string path);
	void createLevel(std::shared_ptr<CollisionManager> collisionManager);
	void renderLevel(SDL_Renderer * renderer);

};

