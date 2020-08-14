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

void Cursor::update(const float& p_dt)
{
	// Set the cursor pos to be the mouse pos
	setPos(*controls->getWorldMousePos());

	// clamp it
	if (pos.x >= 32.f)
	{
		pos.x = 32.f;
	}

	if(pos.y >= 32.f)
		pos.y = 32.f;

	if (pos.x <= -32.f)
	{
		pos.x = -32.f;
	}

	if(pos.y <= -32.f)
		pos.y = -32.f;

	// If the user is pressing left mouse, move the slotted sprite
	if (controls->isLeftClick() && slot)
	{
		if (slot->isInteractsWithCursor())
		{
			slot->setIsClicked(true);
			slot->setPos(getPos());
		}
	}

	if (!(controls->isLeftClick()) && slot)
	{
		slot->setIsClicked(false);
		std::cout << "haha" << std::endl;
	}
}

void Cursor::onCollisionBegin(Sprite* p_sprite)
{	
	// Nothing here
}

void Cursor::onCollisionEnd(Sprite* p_sprite)
{
	// If the collision ends with a sprite,
	// and the sprite is in the slot, remove the sprite from the slot
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
	if (p_sprite != nullptr)
		slotFull = true;
	else
		slotFull = false;
}

bool Cursor::isSlotFull()
{
	return slotFull;
}