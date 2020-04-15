#pragma once

#include <vector>
#include <SDL.h>
#include <iostream>
#include "GameState.h"

/**
	Component for controlling entities in the game.
*/

class InputComponent
{
private:
	SDL_Event event{};/*!<SDL_Event to read input from keyboard*/
	const int speed = 8;/*!<The speed in pixels wich the different entities move at*/

public:
	/**
		Function for checking for input from keyboard
		\param window SDL_Window in which the input will be coming from
		\param speedXY array for handling in which direction the entity is moving
		\param gameState used for sending back gamestate to the GameManager depending on input recieved
	*/
	virtual void update(int speedXY[2], std::shared_ptr<GameState> gameState);
	std::string mainUpdate(std::shared_ptr<GameState> gameState);
	InputComponent();
};
