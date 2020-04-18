#include "InputComponent.h"


void InputComponent::update(std::shared_ptr<MovingEntity> entityBeingController, std::shared_ptr<GameState> gameState, bool atIntersection)
{
	std::vector<int> lastVelocity = entityBeingController->velocity;
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
				if (atIntersection) {
					entityBeingController->velocity[0] = 0;
					entityBeingController->velocity[1] = -entityBeingController->getSpeed();
				}
				else {
					entityBeingController->velocity[0] = -lastVelocity[0];
					entityBeingController->velocity[1] = -lastVelocity[1];
				}


				break;

			case SDLK_DOWN:
				if (atIntersection) {
					entityBeingController->velocity[0] = 0;
					entityBeingController->velocity[1] = entityBeingController->getSpeed();
				}
				else {
					entityBeingController->velocity[0] = -lastVelocity[0];
					entityBeingController->velocity[1] = -lastVelocity[1];
				}


				break;

			case SDLK_LEFT:
				if (atIntersection) {
					entityBeingController->velocity[0] = -entityBeingController->getSpeed();
					entityBeingController->velocity[1] = 0;
				}
				else {
					entityBeingController->velocity[0] = -lastVelocity[0];
					entityBeingController->velocity[1] = -lastVelocity[1];
				}

				break;

			case SDLK_RIGHT:
				if (atIntersection) {
					entityBeingController->velocity[0] = entityBeingController->getSpeed();;
					entityBeingController->velocity[1] = 0;
				}
				else {
					entityBeingController->velocity[0] = -lastVelocity[0];
					entityBeingController->velocity[1] = -lastVelocity[1];
				}


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




