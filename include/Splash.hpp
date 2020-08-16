#pragma once

#include <map>
#include <string>

#include "Sprite.hpp"
#include "Animation.hpp"

class Splash : public Sprite
{
public:
	Splash();
	Splash(const SpriteCreateInfo& p_info);

	void update(const float& p_dt) override;

private:
	float alphaDelta;
	float fAlpha;
	float alphaLifeTime;
};