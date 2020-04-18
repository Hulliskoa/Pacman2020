#pragma once
#include "InputComponent.h"
#include "CollisionManager.h"
#include "Entity.h"
#include <iostream> 
#include <iterator> 
#include <map> 
#include <algorithm>
#include <functional>

/*! \brief
 *		Controls the ghosts
 *
 *
 * By using pytagoras to calculate the shortest path from ghost to pacman this class choose the next tile to travel to based on that.
 * The game board is split up into tiles. Some of these tile is so called intersections. On these intersections this class is allow to do its calculation.
 */
class AiComponent : public InputComponent
{
private:
	std::vector<int> m_targetTile;/*!< The target that currently is the target for the calculation being done*/
	std::vector<int> m_lastVelocity;/*!< Last rounds direction the ghost was travelling */
	std::vector <int> m_firstV;/*!< The first tile left of the direction that is travelled */
	std::vector<int> m_secondV;/*!< The second tile left of the direction that is travelled */
	std::vector<int> m_thirdV;/*!< The third tile left of the direction that is travelled */
	std::map<int, std::vector<int>> m_shortestPath;/*!< A map of all the paths that can be chosen */
	bool m_targetSet = false;/*!< boolean to check if other target than pacman i set*/
	std::vector<int> m_tilesChecked = { 0,0,0 };/*!< stores the distance values for each of the tiles that are checked*/ 

public:
	AiComponent();

	/**Sets a new target other than pacman. Used when ghosts are fleeing or returnin to cage after being eaten
		\param x x-coordinate to target position
		\param y x-coordinate to target position
	*/
	void setTarget(int x, int y);

	/**The update method uses a switch statement to send its parameter on to the actual ai methods
		\param currentGhost the ghost that is currently being controlled by the AI
		\param ghostAi a number between 0 and 3 for selecting wich AI we want to use
		\param pacman a smart pointer to the pacman object
		\param collisionManager the global collision manager. To make decision based on what is currently on the tiles around the ghost
		\param gameState the global gameState to make decisions based on this
	*/
	void update(std::shared_ptr<Entity> currentGhost, int ghostAi, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState);

	/**Sets up conditions for this particular ai and feeds that input on to the actual ai method
		\param currentGhost the ghost that is currently being controlled by the AI
		\param pacman a smart pointer to the pacman object
		\param collisionManager the global collision manager. To make decision based on what is currently on the tiles around the ghost
		\param gameState the global gameState to make decisions based on this
	*/
	void shadowAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState);
	
	/**See description for shadowAI

	*/
	void speedyAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManage, std::shared_ptr<GameState> gameState);

	/**See description for shadowAI

	*/
	void bashfulAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState);
	
	/**See description for shadowAI

	*/
	void pokeyAI(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState);
	
	/**The AI algorithm for making decision based on distance to pacman. The algorithm checks three tiles around the ghost. Left, Front and Right based on the direction it is travelling.
	*Then it calculates the hypotenus between the ghost and pacman based on an imagined triangle between them. The result of this calculation is saved as a key in the shortestPath map together with 
	* the vector of coordinates to the tile that was used for calculating the distance. If one or more of the tiles are walls or other obstacles the calculation will not be done for those tiles. At the end the 
	* map is used for selecting the tile that gets the ghost closer to pacman. This is done by selecting the first element in the map since this key automatically will be the one that is the lowest.
		\param currentGhost the ghost that is currently being controlled byu the AI
		\param ghostAi a number between 0 and 4 for selectin wich AI we want to use
		\param pacman a smart pointer to the pacman object
		\param collisionManager the global collision manager. To make decision based on what is currently on the tiles around the ghost
		\param gameState the global gameState to make decisions based on this
	*/
	void ai(std::shared_ptr<Entity> currentGhost, std::shared_ptr<Entity> pacman, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<GameState> gameState);
	
	/** Checks if the ghost is back in the cage
		\param currentGhost the ghost that is currently being controlled by the AI
		\param collisionManager a number between 0 and 4 for selecting wich AI we want to use

	*/
	bool checkIfReturn(std::shared_ptr<Entity> currentGhost, std::shared_ptr<CollisionManager> collisionManager);

	/** Remove manually set target and resets target back to pacman

	*/
	void removeTarget();
};

