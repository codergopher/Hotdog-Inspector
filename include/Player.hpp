#pragma once

#include <map>
#include <string>

#include "Sprite.hpp"
#include "Animation.hpp"
#include "Controls.hpp"

class Player : public Sprite
{
public:
	Player();
	Player(const SpriteCreateInfo& p_info);

	void update(const float& p_dt) override;

	void animate(const float& p_dt);

private:
	std::map<std::string, AnimationCycle> animationSet;

};