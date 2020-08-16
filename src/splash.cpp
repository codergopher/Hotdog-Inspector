#include "Splash.hpp"
#include "Cursor.hpp"
Splash::Splash() {}

Splash::Splash(const SpriteCreateInfo& p_info)
:Sprite::Sprite(p_info),
alphaDelta(100.f),
fAlpha(1),
alphaLifeTime(100.f)
{
	
	loadFrames(frameSize);
	currentFrame = frames[0];

}

void Splash::update(const float& p_dt)
{
	std::cout << fAlpha << std::endl;
	if (alpha >254)
		alphaDelta = -100.f;


	fAlpha += alphaDelta * p_dt;
	alpha = roundToInt(fAlpha);

	if (alpha < 1)
	{
		pleaseDelete = true;
	}
}
