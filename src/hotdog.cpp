#include "Hotdog.hpp"

#include "Conveyor.hpp"

Hotdog::Hotdog()
{

}

<<<<<<< HEAD
Hotdog::Hotdog(const SpriteCreateInfo& p_info, Lives* p_lifeCounter)
:Sprite(p_info), 
=======
Hotdog::Hotdog(const SpriteCreateInfo& p_info)
:Sprite(p_info),
canKill(true),
>>>>>>> a34f7444bd6dad1b10b13d4dd48345a1c53fc223
isDying(false),
fAlpha(255),
scaleLifeTime(1.f),
alphaLifeTime(300.f),
<<<<<<< HEAD
lifeCounter(p_lifeCounter),
targetPos(0, 0),
=======
targetPos(nullptr),
lastTargetPos(pos),
>>>>>>> a34f7444bd6dad1b10b13d4dd48345a1c53fc223
lag(0.1f)

{
	lastTargetPos = pos;
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

	if(targetPos)
	{
		Vector2f dis = *targetPos - pos;
		Vector2f vel = dis * lag;

		move(vel);	
	}

	if (!clicked && !targetPos)
	{
		Vector2f dis = lastTargetPos - pos;
		Vector2f vel = dis * lag;
		move(vel);		
	}

	if (!clicked && !targetPos)
		canKill = false;
}

void Hotdog::onCollisionBegin(Sprite* p_sprite)
{

}

void Hotdog::duringCollision(Sprite* p_sprite)
{

	Conveyor* conveyor = dynamic_cast<Conveyor*>(p_sprite);
	if (conveyor)
	{
		std::cout << "lol" << std::endl;
		//targetPos = &p_sprite->getPos();
		move(Vector2f(conveyor->getSpeed()));
		lastTargetPos += conveyor->getSpeed();
		canKill = true;
	}

	if (p_sprite->getName() == "Trash Can" && !clicked && canKill)
	{
		isDying = true;
		clickable = false;
<<<<<<< HEAD
		targetPos = p_sprite->getPos();
		if (name == "Good Hotdog")
		{
			lifeCounter->removeLife();
		}
=======
		targetPos = &p_sprite->getPos();
>>>>>>> a34f7444bd6dad1b10b13d4dd48345a1c53fc223
	}

	if (p_sprite->getName() == "Crate" && !clicked && canKill)
	{
		isDying = true;
		clickable = false;
<<<<<<< HEAD
		targetPos = p_sprite->getPos();
		if (name == "Bad Hotdog" || name == "Hotdog Finger")
		{
			lifeCounter->removeLife();
		}
=======
		targetPos = &p_sprite->getPos();
>>>>>>> a34f7444bd6dad1b10b13d4dd48345a1c53fc223
	}
}

void Hotdog::onCollisionEnd(Sprite* p_sprite)
{

}