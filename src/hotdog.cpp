#include "Hotdog.hpp"

Hotdog::Hotdog()
{

}

Hotdog::Hotdog(const SpriteCreateInfo& p_info)
:Sprite(p_info),
isDying(false),
fAlpha(255),
scaleLifeTime(1.f),
alphaLifeTime(300.f),
targetPos(0, 0),
lag(0.1f)
{

}

void Hotdog::update(const float& p_dt)
{
	if (isDying)
	{
		Vector2f dis = targetPos - pos;
		Vector2f vel = dis * lag;

		move(vel);

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

}

void Hotdog::duringCollision(Sprite* p_sprite)
{
	if (p_sprite->getName() == "Trash Can" && !clicked)
	{
		isDying = true;
		clickable = false;
		targetPos = p_sprite->getPos();
	}

	if (p_sprite->getName() == "Crate" && !clicked)
	{
		isDying = true;
		clickable = false;
		targetPos = p_sprite->getPos();
	}
}

void Hotdog::onCollisionEnd(Sprite* p_sprite)
{

}