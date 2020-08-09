#include "Animation.hpp"

#include <jsoncpp/json/json.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include "Math.hpp"

void Frame::print()
{
	std::cout << "x: " << rect.x << "\n" << "y: " << rect.y << "\n" << "w: " << rect.w << "\n" << "h: " << rect.h << std::endl;
	std::cout << "duration: " << duration << std::endl;  
}

std::map<std::string, AnimationCycle> loadAnimationFile(const char* p_filePath)
{
    //load a anim file
	Json::Value root;

	std::ifstream ifs;
	ifs.open(p_filePath);

	Json::CharReaderBuilder builder;
	builder["collectComments"] = true;
	JSONCPP_STRING errs;

	if (!parseFromStream(builder, ifs, &root, &errs))
		std::cout << errs << std::endl;

	// seperate the frames from the meta
	const Json::Value frames = root["frames"];

	const Json::Value meta = root["meta"];

	// the animation cycles
	

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

		allFrames.push_back(frame);
	}

	std::map<std::string, AnimationCycle> cycles;

	const Json::Value jsonFrameTags = meta["frameTags"];

	// break up the frames into different cycles

	for (Uint8 i=0; i < jsonFrameTags.size(); ++i)
	{
		AnimationCycle c;

		const Json::Value tag = jsonFrameTags[i]; 

		c.name = tag["name"].asString();
		c.playBackSpeed = 1.f;
		c.currentFrame = 0;
		c.delta = 0;

		int start = std::stoi(tag["from"].asString());
		int end = std::stoi(tag["to"].asString());

		for (int j = start; j <= end; ++j)
		{
			c.frames.push_back(allFrames[j]);
		}

		cycles.insert(std::pair<std::string, AnimationCycle>(c.name, c));
	}

	return cycles;

}
