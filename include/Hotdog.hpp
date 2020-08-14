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
	void onCollisionEnd(Sprite* p_sprite) override;
private:
	bool isDying;

	float fAlpha;
	float scaleLifeTime;
	float alphaLifeTime;
};