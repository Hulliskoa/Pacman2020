#pragma once
#include <vector>
#include "MovingEntity.h"
#include <SDL.h>
#include <fstream>
#include <iostream>
#include "CollisionManager.h"

/**
	LevelManager renders and creates each level from .txt files containing ascii drawings of the level to be rendered.
	All stationary objects on the level is created here and rendered by this class. 
*/
class LevelManager
{
private:
	//int currentLevel;
	char levelArray[31][28] = {};
	std::vector<std::shared_ptr<Entity>> entityArray;
	std::vector<std::string> levels;
	SDL_Renderer* renderer;
	SDL_Surface* mazeSprites;
	SDL_Texture* m_texture = nullptr;
	int m_textureWidth = 0;
	int m_textureHeight = 0;

	int xOffset = 3;
	int yOffset = 4;
public:
	LevelManager(SDL_Renderer* mainRenderer);
	~LevelManager();
	void free();
	void createLevel(std::shared_ptr<CollisionManager> collisionManager, int currentLvl);
	bool loadFromFile(SDL_Surface* mainSpriteSheet);
	void renderLevel();

};

