#pragma once

#include <map>
#include <string>

#include "Sprite.hpp"
#include "Animation.hpp"

class Character : public Sprite
{
public:
	//~Character();
	Character();
	Character(const SpriteCreateInfo& p_info, std::string p_character);

	void update(const float& p_dt) override;

	void setCharacter(std::string p_character);

	void animate(const float& p_dt);

private:
	std::string character;
	std::string laracter;
	std::map<std::string, AnimationCycle> animationSet;
};