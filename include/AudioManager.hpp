//AudioManager.hpp

#pragma once

#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>
#include <iostream>
class AudioManager
{
public:
	AudioManager();
	void play(std::string p_clip, int p_loops);
private:
	std::map<std::string, Mix_Chunk*> clips;
};
