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