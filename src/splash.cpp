#include "Splash.hpp"
#include "Cursor.hpp"
Splash::Splash() {}

Splash::Splash(const SpriteCreateInfo& p_info)
:Sprite::Sprite(p_info),
fAlpha(255),
alphaLifeTime(100.f)
{
	
	loadFrames(frameSize);
	currentFrame = frames[0];

}

void Splash::update(const float& p_dt)
{
	if (alpha > 0)
	{
		fAlpha -= alphaLifeTime * p_dt;
		alpha = roundToInt(fAlpha);
	}
	else
	{
		pleaseDelete = true;
	}
}
