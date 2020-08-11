#pragma once

#include <map>
#include <string>

#include "Sprite.hpp"
#include "Animation.hpp"
#include "Clickable.hpp"

class Character : public Sprite
{
public:
	Character();
	Character(const SpriteCreateInfo& p_info, std::string p_character);

	void update(const float& p_dt) override;

	void animate(const float& p_dt);

private:
	std::string character;
	std::map<std::string, AnimationCycle> animationSet;
};