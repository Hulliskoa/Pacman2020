#include "InputComponent.h"

void InputComponent::update(SDL_Event event)
{

	while (SDL_PollEvent(&event) != 0)
	{
		//User requests quit
		if (event.type == SDL_QUIT)
		{
			//globalPause = true;
		}
		//User presses a key
		else if (event.type == SDL_KEYDOWN)
		{
			//Select surfaces based on key press
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				speedXY[0] = 0;
				speedXY[1] = 1;
				break;

			case SDLK_DOWN:
				speedXY[0] = 0;
				speedXY[1] = -1;
				break;

			case SDLK_LEFT:
				speedXY[0] = -1;
				speedXY[1] = 0;
				break;

			case SDLK_RIGHT:
				speedXY[0] = 1;
				speedXY[1] = 0;
				break;

			default:
				break;
			}
		}
	}
}

int* InputComponent::getSpeed()
{
	return speedXY;
}

InputComponent::InputComponent() {
	speedXY[0] = {};
}


