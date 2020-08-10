#include "Animation.hpp"

#include <json/json.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include "Math.hpp"

// Print the frame, for debugging purposes
void Frame::print()
{
	std::cout << "x: " << rect.x << "\n" << "y: " << rect.y << "\n" << "w: " << rect.w << "\n" << "h: " << rect.h << std::endl;
	std::cout << "duration: " << duration << std::endl;  
}

// Create a std::map with a string as a key to the values.
// This creates a set of animations from a .json Libresprite file
std::map<std::string, AnimationCycle> loadAnimationFile(const char* p_filePath)
{
    //Everything inside the .json
	Json::Value root;

	std::ifstream ifs;
	ifs.open(p_filePath);

	Json::CharReaderBuilder builder;
	builder["collectComments"] = true;
	JSONCPP_STRING errs;

	// load everything in the file into root
	if (!parseFromStream(builder, ifs, &root, &errs))
		std::cout << errs << std::endl;

	// seperate the frames from everything else
	const Json::Value frames = root["frames"];

	// Seperate the meta data(tags) from everything else
	const Json::Value meta = root["meta"];

	// Store all of the frames. Will sort them into seperate
	// animation cycles later
	std::vector<Frame> allFrames = {};

	for (Uint8 i=0; i < frames.size(); ++i)
	{
		// intermediate json frames for each info bit
		const Json::Value jsonFrame = frames[i];
		const Json::Value jsonRect = jsonFrame["frame"];

		// the temporary frame
		Frame frame;

		// copy those goody gremlins
		frame.duration = std::stoi(jsonFrame["duration"].asString());
		frame.rect.x =  std::stoi(jsonRect["x"].asString());
		frame.rect.y =  std::stoi(jsonRect["y"].asString());
		frame.rect.w =  std::stoi(jsonRect["w"].asString());
		frame.rect.h =  std::stoi(jsonRect["h"].asString());

		// and create a new frame
		allFrames.push_back(frame);
	}

	// From here, we seperate all of th frames into their
	// respective AnimationCycle

	std::map<std::string, AnimationCycle> cycles;

	// Get the frame tags from the meta data
	const Json::Value jsonFrameTags = meta["frameTags"];

	// break up the frames into different cycles

	for (Uint8 i=0; i < jsonFrameTags.size(); ++i)
	{
		// Temporary Animation cycle
		AnimationCycle c;

		// Get a tag from the meta data
		const Json::Value tag = jsonFrameTags[i]; 

		// Fill out the Animation cycle meta data
		c.name = tag["name"].asString();
		c.playBackSpeed = 1.f;
		c.currentFrame = 0;
		c.delta = 0;

		// And last but not least tuck all of the the 
		// animation cycle's respective frames into the cycle
		int start = std::stoi(tag["from"].asString());
		int end = std::stoi(tag["to"].asString());

		for (int j = start; j <= end; ++j)
		{
			c.frames.push_back(allFrames[j]);
		}

		// Create a new animation cycle, and name it to be the cycle tag
		cycles.insert(std::pair<std::string, AnimationCycle>(c.name, c));
	}

	return cycles;
}
