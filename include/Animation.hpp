//Animation.hpp

#pragma once

#include <json/json.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include "Math.hpp"

// A frame is a rectangular section of a texture

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

// An AnimationCycle is a collection of frames, plus other data.

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
	// The frame currently being rendered in the cycle
	Uint8 currentFrame;

	// A counter that must accumulate to a set number before the next frame
	float delta;

	float playBackSpeed;
	std::string name;
	std::vector<Frame> frames;
};

// Creates a set of AnimationCycles, and the std::string is the tag of the cycle in the libresprite .json
std::map<std::string, AnimationCycle> loadAnimationFile(const char* p_filePath);
