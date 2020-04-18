#include "InputComponent.h"


void InputComponent::update(std::shared_ptr<MovingEntity> entityBeingControlled, std::shared_ptr<GameState> gameState)
{
	std::vector<int> lastVelocity = entityBeingControlled->velocity;
	
	while (SDL_PollEvent(&event) != 0)
	{

		if (event.type == SDL_QUIT)
		{
			*gameState = GameState::EXIT_GAME;
			break;

		}
		//User presses a key
		if (event.type == SDL_KEYDOWN)
		{

			//Select surfaces based on key press
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				entityBeingControlled->velocity[0] = 0;
				entityBeingControlled->velocity[1] = -entityBeingControlled->getSpeed();
				break;

			case SDLK_DOWN:
				entityBeingControlled->velocity[0] = 0;
				entityBeingControlled->velocity[1] = entityBeingControlled->getSpeed();
				break;

			case SDLK_LEFT:
				entityBeingControlled->velocity[0] = -entityBeingControlled->getSpeed();
				entityBeingControlled->velocity[1] = 0;
				break;

			case SDLK_RIGHT:
				entityBeingControlled->velocity[0] = entityBeingControlled->getSpeed();
				entityBeingControlled->velocity[1] = 0;
				break;

			case SDLK_ESCAPE:
				*gameState = GameState::MAIN_MENU;
				break;

			default:
				break;
			}

		}
	}
}






std::string InputComponent::mainUpdate(std::shared_ptr<GameState> gameState)
{

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			*gameState = GameState::EXIT_GAME;
			break;

		}
		//User presses a key
		if (event.type == SDL_KEYDOWN)
		{

			//Select surfaces based on key press
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				return "UP";
				break;

			case SDLK_DOWN:
				return "DOWN";
				break;

			case SDLK_LEFT:
				return "LEFT";
				break;

			case SDLK_RIGHT:
				return "RIGHT";
				break;
			case SDLK_ESCAPE:
				return "ESC";
				break;

			case SDLK_RETURN:
				return "RETURN";
				break;

			default:
				return "";
				break;
			}
		}
	}
	return "";
}

InputComponent::InputComponent() {}




