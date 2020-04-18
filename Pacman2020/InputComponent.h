#pragma once

#include <vector>
#include <SDL.h>
#include <iostream>
#include "GameState.h"
#include "MovingEntity.h"
/**
	Component for controlling entities in the game.
*/

class InputComponent
{
private:
	SDL_Event event{};/*!<SDL_Event to read input from keyboard*/

public:
	/**
		Function for checking for input from keyboard
		\param entityBeingController entity object for accessing and editing the direction the entity is moving
		\param gameState used for sending back gamestate to the GameManager depending on input recieved
	*/
	virtual void update(std::shared_ptr<MovingEntity>  entityBeingController, std::shared_ptr<GameState> gameState);
	/**
		Function for checking for input from keyboard
		\param gameState supplies games state to be able to quit when someone click the x on the window

	*/
	std::string mainUpdate(std::shared_ptr<GameState> gameState);
	InputComponent();
};
