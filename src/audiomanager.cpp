#include "AudioManager.hpp"


AudioManager::AudioManager()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	//add clips
	clips.insert(std::pair<std::string, Mix_Chunk*>("spawn", Mix_LoadWAV("romfs:/music/spawn.wav")));
	clips.insert(std::pair<std::string, Mix_Chunk*>("correct", Mix_LoadWAV("romfs:/music/correct.wav")));
	clips.insert(std::pair<std::string, Mix_Chunk*>("wrong", Mix_LoadWAV("romfs:/music/wrong.wav")));
	clips.insert(std::pair<std::string, Mix_Chunk*>("track_0", Mix_LoadWAV("romfs:/music/0.wav")));
	clips.insert(std::pair<std::string, Mix_Chunk*>("click", Mix_LoadWAV("romfs:/music/click.wav")));
}

void AudioManager::play(std::string p_clip, int p_loops)
{
	Mix_PlayChannel(-1, clips[p_clip], p_loops);
}
