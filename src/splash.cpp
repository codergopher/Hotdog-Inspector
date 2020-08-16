#include "Splash.hpp"
#include "Cursor.hpp"
Splash::Splash() {}

Splash::Splash(const SpriteCreateInfo& p_info)
:Sprite::Sprite(p_info),
alphaDelta(90.f),
fAlpha(1),
alphaLifeTime(100.f)
{
	
	loadFrames(frameSize);
	currentFrame = frames[0];

}

void Splash::update(const float& p_dt)
{
	if (fAlpha >254)
		alphaDelta = -90.f;


	fAlpha += alphaDelta * p_dt;
	color.r = roundToInt(fAlpha);
	color.g = roundToInt(fAlpha);
	color.b = roundToInt(fAlpha);
	if (fAlpha < 1)
	{
		pleaseDelete = true;
	}
}
