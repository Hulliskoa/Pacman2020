#pragma once
#include <vector>
#include "MovingEntity.h"
#include <SDL.h>
#include <fstream>
#include <iostream>
#include "CollisionManager.h"

/*! \brief
 *		Renders and creates each level based on .txt files
 *
 *
 * Each .txt file contains ascii drawings of the level to be rendered.
 * All stationary objects on the level is created and rendered by this class.
 */
class LevelManager
{
private:
	char levelArray[31][28] = {};/*!<Array containing all char's in the .txt file that was loaded for the current map*/
	std::vector<std::shared_ptr<Entity>> entityArray;/*!< an array of entities for use when rendering map. This i populated by a controlstructure checking what symbol was loaded in the levelArray*/
	std::vector<std::shared_ptr<Entity>> ghostDoors;/*!< an array containing entity objects for the doors to the ghost cage*/
	SDL_Renderer* renderer;/*<!main renderer supplied by the Game manager*/
	SDL_Texture* m_levelSpriteSheet = nullptr;/*<! spritesheet texture used to render the maze*/
	int m_textureWidth = 0;/*<! width of the texture used to render the maze*/
	int m_textureHeight = 0;/*<! height of the texture used to render the maze*/
	int m_xMapOffset = 1;/*<! x offset to where the sprites should be rendered inside the sdl window*/
	int m_yMapOffset = 4;/*<! y offset to where the sprites should be rendered inside the sdl window*/
	int m_startingPelletCount = 0;
	int m_currentLvl = 1;/*!<Keeps track of the current level*/
	int m_currentMap = 1;/*!<Keeps track of the current map to be loaded*/
	std::ifstream m_lvlFile;
public:

	LevelManager(SDL_Renderer* mainRenderer);
	~LevelManager();

	/**
		Used to read .txt file and convert it into the levelArray
		\param currentLvl used when loading the .txt file. the naming of each file is "lvl#.txt"
	*/
	bool readLevelFromTxt(int currentLvl);

	/**
		Used to load the spritesheet into a texture for use when creating entities and rendering
		\param path to spritesheet png
	*/
	bool loadspriteSheetTexture(std::string path);

	/**
		Creates lvl in the form of entity objects
		\param collisionManager global collision manager is supplied so that every entity created can be push into the collision vector
	*/
	void createLevel(std::shared_ptr<CollisionManager> collisionManager);

	/**
		Renders level to screen and makes use of the entityArray to load each entity created.
		\param renderer needs to supply renderer to
	*/
	void renderLevel(SDL_Renderer* renderer);
	/**
		Creates intersections where the ghosts are able to make decisions
		\param collisionManager used for adding intersections to the collision check vector
	*/
	void createInterSections(std::shared_ptr<CollisionManager> collisionManager);
	/**
		Counts the amount of pellets remaining on the map
	*/
	int pelletCount();
	/**
		Counts the total amount of pellets
	*/
	int getStartingPelletCount();
	/**
		opens doors to the ghost cage
	*/
	void openDoors();
	/**
		opens doors to the ghost cage
	*/
	void closeDoors();
	/**
		returns current lvl
	*/
	int getCurrentLevel();
	/**
		set currentLevel member variable to 1;
	*/
	void resetLevels();

};

