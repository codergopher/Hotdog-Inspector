#pragma once

#include <map>
#include <string>

#include "Math.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "Life.hpp"

class Lives
{
public:
	Lives();
	Lives(const SpriteCreateInfo& p_info, Uint8 p_lives);
	bool updateLives(Uint8 p_lives);
	bool removeLife();
	Uint8 getLifeCount();
	Sprite& getLives(Uint8 p_index);

private:
	Uint8 lifeCount;
	Uint8 spacing;
	std::vector<Life> lives;
	std::map<std::string, AnimationCycle> animationSet;
};