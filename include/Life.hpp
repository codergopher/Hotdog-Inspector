#pragma once

#include <map>
#include <string>

#include "Sprite.hpp"
#include "Animation.hpp"
//TODO: FINISH THIS
class Life : public Sprite
{
public:
	Life();
	Life(const SpriteCreateInfo& p_info);

	void update(const float& p_dt) override;

	void animate(const float& p_dt);

	void updateIcon(bool p_value);


private:
	bool icon = false;
	std::map<std::string, AnimationCycle> animationSet;
};