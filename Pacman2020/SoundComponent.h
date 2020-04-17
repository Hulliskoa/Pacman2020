#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

class SoundComponent
{
private:
	Mix_Chunk* soundEffect = nullptr;
	std::string pathToMedia;
public:
	SoundComponent(std::string path);
	bool loadMedia();
	void play(int playLoop, int volume);
	void playMusic();
	void stop();
	~SoundComponent();
};