#pragma once

#include <map>
#include <string>

#include "Math.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"

class Lives
{
public:
	Lives();
	Lives(const SpriteCreateInfo& p_info, Uint8 p_lives);
	bool updateLives(Uint8 p_lives);
	bool removeLife();
	Uint8 getLives();
	Sprite& getSprite(Uint8 p_index);

private:
	Uint8 lives;
	Uint8 spacing;
	std::vector<Sprite> UIsprites;
	std::map<std::string, AnimationCycle> animationSet;
};