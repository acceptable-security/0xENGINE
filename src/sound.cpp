#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "sound.h"

Sound::Sound(std::string filename, bool _loop)
{
	loop = _loop;
	audio = Mix_LoadWAV(filename.c_str());
}

void Sound::play()
{
	if(loop)
	{
		Mix_PlayChannel(-1, audio, -1);
	}
	else
	{
		Mix_PlayChannel(-1, audio, 0);
	}
}

void Sound::stop()
{
	Mix_HaltChannel(-1);
}

void Sound::free()
{
	Mix_FreeChunk(audio);
}