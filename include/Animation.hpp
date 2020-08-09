#pragma once

#include <jsoncpp/json/json.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include "Math.hpp"

struct Frame
{
	Frame(){}

	Frame(IntRect p_rect, float p_duration, SDL_Texture* p_tex)
	:rect(p_rect), duration(p_duration), tex(p_tex)
	{
	}

	void print();
	IntRect rect;
	int duration;
	SDL_Texture* tex;
};

struct AnimationCycle
{
	AnimationCycle()
	: currentFrame(0),
	delta(0.f),
	playBackSpeed(1.f),
	name("blank")
	{
	}
	~AnimationCycle() {}
	uint currentFrame;
	float delta;
	float playBackSpeed;
	std::string name;
	std::vector<Frame> frames;
};


std::map<std::string, AnimationCycle> loadAnimationFile(const char* p_filePath);
