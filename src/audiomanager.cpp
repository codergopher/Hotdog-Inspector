/*#include "AudioManager.hpp"

AudioManager::AudioManager()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	//add clips
	clips.insert(std::pair<const char*, Mix_Chunk*>("hit", Mix_LoadWAV("res/music/hit.wav")));
	clips.insert(std::pair<const char*, Mix_Chunk*>("correct", Mix_LoadWAV("res/music/correct.wav")));
	clips.insert(std::pair<const char*, Mix_Chunk*>("wrong", Mix_LoadWAV("res/music/wrong.wav")));
	clips.insert(std::pair<const char*, Mix_Chunk*>("track_0", Mix_LoadWAV("res/music/0.wav")));
}

void AudioManager::play(const char* p_clip)
{
	Mix_PlayChannel(-1, clips[p_clip], 0);
}
*/