#include "Cursor.hpp"

void Cursor::setTarget(const Vector2f* p_target)
{
	target = p_target;
}

void Cursor::update(const float& p_dt)
{
	// Set the cursor pos to be the mouse pos
	setPos((*target));
}

void Cursor::onCollisionBegin(Sprite* p_sprite)
{	
	std::cout << "On begin" << std::endl;
	slot0 = p_sprite;
}

void Cursor::onCollisionEnd(Sprite* p_sprite)
{
	slot0 = nullptr;
	std::cout << "On end!" << std::endl;
}