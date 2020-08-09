#pragma once

#include <map>
#include <string>

#include "Sprite.hpp"
#include "Animation.hpp"

class Conveyor : public Sprite
{
public:
	Conveyor();
	Conveyor(const SpriteCreateInfo& p_info);

	void update(const float& p_dt) override;

	void animate(const float& p_dt);

private:
	std::map<std::string, AnimationCycle> animationSet;

};