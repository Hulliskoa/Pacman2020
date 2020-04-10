#pragma once
#include <vector>
#include "MovingEntity.h"
#include <SDL.h>
#include <fstream>
#include <iostream>
#include "CollisionManager.h"


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
	int m_width = 0;
	int m_height = 0;
public:
	LevelManager(SDL_Renderer* mainRenderer);
	//void update();
	~LevelManager();
	void free();
	void createLevel(std::shared_ptr<CollisionManager> collisionManager, int currentLvl);
	//void update(SDL_Renderer* renderer);
	bool loadFromFile(SDL_Surface* mainSpriteSheet);
	void renderLevel();

};

