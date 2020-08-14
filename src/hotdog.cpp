#include "Hotdog.hpp"

Hotdog::Hotdog()
{

}

Hotdog::Hotdog(const SpriteCreateInfo& p_info)
:Sprite(p_info),
isDying(false),
fAlpha(255),
scaleLifeTime(1.f),
alphaLifeTime(300.f)
{

}

void Hotdog::update(const float& p_dt)
{
	if (isDying)
	{
		scale -= scaleLifeTime * p_dt;


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
}

void Hotdog::onCollisionBegin(Sprite* p_sprite)
{
	if (p_sprite->getName() == "Trash Can")
	{
		std::cout << "oh yeah" << std::endl;
		isDying = true;
		clickable = false;
	}
}

void Hotdog::onCollisionEnd(Sprite* p_sprite)
{

}