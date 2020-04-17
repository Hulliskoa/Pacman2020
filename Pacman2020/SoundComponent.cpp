#include "SoundComponent.h"
SoundComponent::SoundComponent(std::string path) : pathToMedia(path) {
	if (!loadMedia()) {
		std::cout << "Could not load media" << std::endl;
	}
}

SoundComponent::~SoundComponent()
{
	Mix_FreeChunk(soundEffect);
	soundEffect = NULL;
}



bool SoundComponent::loadMedia() {

	bool success = true;
	//Load sound effects
	soundEffect = Mix_LoadWAV(pathToMedia.c_str());
	if (soundEffect == NULL)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;;
		success = false;
	}



	return success;
}

void SoundComponent::play(int playLoop, int volume)
{
	soundEffect->volume = volume;
	Mix_PlayChannel(-1, soundEffect, playLoop);
}

void SoundComponent::stop()
{
	Mix_PlayChannel(-1, soundEffect, 0);
}
