#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

/*! \brief
 *		Wrapper object for playing sound in game
 *
 *
 *	Each sound in the game is created with a sound component
 */
class SoundComponent
{
private:
	Mix_Chunk* soundEffect = nullptr;/*!<SDL Mixer Mix chunk for storing adn playing sound*/
	std::string pathToMedia;/*!<Path to sound*/
public:
	/**
		Constructor
		\param path path to sound we want to use
	*/
	SoundComponent(std::string path);
	/**
		Loads sound file int soundEffect Mix Chunk
	*/
	bool loadMedia();
	/**
		Plays back Mix_Chunk object
		\param channel channel to play sound on (0 or 1);
		\param playLoop -1 loops, 0 plays once, 1 plays twice
		\param volume
	*/
	void play(int channel, int playLoop, int volume);
	/**
		fades current sound out and stops it
	*/
	void fadeOut();
	~SoundComponent();
};