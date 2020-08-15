#include "Crate.hpp"
#include <string>
#include <iostream>

Crate::Crate()
:hotdogAmount(0)
{

}
Crate::Crate(const SpriteCreateInfo& p_info)
:Sprite(p_info),
hotdogAmount(0),
shouldMoveToTarget(false),
targetPos(0.f, 0.f),
lag(0.02f)
{
}

void Crate::onCollisionBegin(Sprite* p_sprite)
{

}

void Crate::duringCollision(Sprite* p_sprite)
{
	Hotdog* hotdog = dynamic_cast<Hotdog*>(p_sprite);

	if (hotdog && hotdogAmount < 6)
	{	
		if (!hotdog->isClicked() && hotdog->isCanKill())
			hotdogAmount++;
	}
}

void Crate::update(const float& p_dt)
{
	if (hotdogAmount > 5)
	{
		clickable = false;

		targetPos = Vector2f(getPos().x, 50.f);

		shouldMoveToTarget = true;

	}

	if(shouldMoveToTarget)
	{
		Vector2f dis = targetPos - pos;
		Vector2f vel = dis * lag;
		move(vel);
	}

	//pos.print();
	if (pos.y > 40.f)
	{
		clickable = true;
		hotdogAmount = 0;
		pos = Vector2f(-44, 17);
		prevPos = pos;
		targetPos = Vector2f(-12, 17);
	}

	if (abs(targetPos.x - pos.x) < 1.f)
		pos.x = targetPos.x;
	if (abs(targetPos.y - pos.y) < 1.f)
		pos.y = targetPos.y;

	animate(p_dt);
}

void Crate::animate(const float& p_dt)
{
	if (hotdogAmount > 6) hotdogAmount = 6;
	play(animationSet[std::to_string(hotdogAmount)]);
}