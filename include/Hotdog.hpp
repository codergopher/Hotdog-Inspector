#pragma once

#include "Sprite.hpp"
#include "Animation.hpp"

class Hotdog : public Sprite
{
public:
	Hotdog();
	Hotdog(const SpriteCreateInfo& p_info);

	void update(const float& p_dt) override;

	void onCollisionBegin(Sprite* p_sprite) override;
	void duringCollision(Sprite* p_sprite) override;
	void onCollisionEnd(Sprite* p_sprite) override;

	bool isCanKill() { return canKill; }
private:


	bool canKill;
	bool isDying;

	float fAlpha;
	float scaleLifeTime;
	float alphaLifeTime;

	Vector2f* targetPos;
	Vector2f lastTargetPos;

	float lag;
};