#ifndef SOUND
#define SOUND
#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class Sound
{
	Mix_Chunk* audio;
	bool loop;
	public:
		Sound::Sound(){};
		Sound::Sound(std::string filename, bool);

		void play();
		void stop();
	
		void free();
};
#endif