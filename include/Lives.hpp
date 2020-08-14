#pragma once

#include <map>
#include <string>

#include "Math.hpp"
#include "Sprite.hpp"

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
	Uint8 spacing = 4;
	std::vector<Sprite> UIsprites;
};