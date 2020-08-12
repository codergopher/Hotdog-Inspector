#include "Cursor.hpp"

void Cursor::setControls(Controls* p_controls)
{
	controls = p_controls;
}

void Cursor::init()
{
	controls = nullptr;
	slot = nullptr;
	slotFull = false;

}

void Cursor::setTarget(const Vector2f* p_target)
{
	target = p_target;
}

void Cursor::update(const float& p_dt)
{
	// Set the cursor pos to be the mouse pos
	setPos((*target));

	if (controls->isLeftClick() && slot)
	{
		slot->setPos(getPos());
	}
}

void Cursor::onCollisionBegin(Sprite* p_sprite)
{	

}

void Cursor::onCollisionEnd(Sprite* p_sprite)
{
	if (p_sprite == slot)
	{
		slot = nullptr;
		slotFull = false;	
	}


}

Sprite* Cursor::getSlot()
{
	return slot;
}
void Cursor::setSlot(Sprite* p_sprite)
{
	slot = p_sprite;
	slotFull = true;
}

bool Cursor::isSlotFull()
{
	return slotFull;
}