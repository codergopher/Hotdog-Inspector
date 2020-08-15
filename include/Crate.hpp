#pragma once

#include "Hotdog.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"

class Crate : public Sprite
{
public:
	Crate();
	Crate(const SpriteCreateInfo& p_info);

	void update(const float& p_dt) override;

	void onCollisionBegin(Sprite* p_sprite) override;
	void duringCollision(Sprite* p_sprite) override;

	void animate(const float& p_dt);
private:
	int hotdogAmount;

	bool shouldMoveToTarget;

	Vector2f targetPos;

	float lag;
};