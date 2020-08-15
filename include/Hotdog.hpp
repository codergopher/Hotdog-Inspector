#pragma once

#include "Sprite.hpp"
#include "Animation.hpp"
#include "Lives.hpp"

class Hotdog : public Sprite
{
public:
	Hotdog();
	Hotdog(const SpriteCreateInfo& p_info, Lives* p_lifeCounter);

	void update(const float& p_dt) override;

	void onCollisionBegin(Sprite* p_sprite) override;
	void duringCollision(Sprite* p_sprite) override;
	void onCollisionEnd(Sprite* p_sprite) override;
private:

	bool isDying;

	float fAlpha;
	float scaleLifeTime;
	float alphaLifeTime;

	Lives* lifeCounter;

	Vector2f targetPos;

	float lag;
};