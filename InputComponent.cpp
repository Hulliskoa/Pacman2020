#include "InputComponent.h"


void InputComponent::update(SDL_Window* window, int speedXY[2])
{

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			SDL_DestroyWindow(window);
			SDL_Quit();
			break;

		}
		//User presses a key
		if (event.type == SDL_KEYDOWN)
		{
			
			//Select surfaces based on key press
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				speedXY[0] = 0;
				speedXY[1] = -speed;
	
				break;

			case SDLK_DOWN:
				speedXY[0] = 0;
				speedXY[1] = speed;
		
				break;

			case SDLK_LEFT:
				speedXY[0] = -speed;
				speedXY[1] = 0;
	
				break;

			case SDLK_RIGHT:
				speedXY[0] = speed;
				speedXY[1] = 0;
			
				break;

			default:
				break;
			}
		}
	}
}

InputComponent::InputComponent(){}




