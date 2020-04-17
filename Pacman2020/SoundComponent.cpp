#include "SoundComponent.h"
SoundComponent::SoundComponent(std::string path) : pathToMedia(path) {
	if (!loadMedia()) {
		std::cout << "Could not load media" << std::endl;
	}
	Mix_AllocateChannels(2);
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

void SoundComponent::play(int channel, int playLoop, int volume)
{
	if (!Mix_Playing(channel)) {
		Mix_PlayChannel(channel, soundEffect, playLoop);
	}
}

void SoundComponent::fadeOut()
{
	Mix_FadeOutChannel(-1, 1000);
}
