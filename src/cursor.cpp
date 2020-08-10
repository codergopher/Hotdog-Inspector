#include "Cursor.hpp"

void Cursor::setTarget(const Vector2f* p_target)
{
	target = p_target;
}

void Cursor::update(const float& p_dt)
{
	std::cout << "haha oh yeah" << std::endl;
	target->print();
	setPos((*target));
}