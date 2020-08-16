#pragma once

#include "Sprite.hpp"
#include "Animation.hpp"

class Furnace : public Sprite
{
public:
	Furnace();
	Furnace(const SpriteCreateInfo& p_info);

	void update(const float& p_dt) override;

	//void onCollisionBegin(Sprite* p_sprite) override;
	//void duringCollision(Sprite* p_sprite) override;

	//void animate(const float& p_dt);
private:
	//std::map<std::string, AnimationCycle> animationSet;
};