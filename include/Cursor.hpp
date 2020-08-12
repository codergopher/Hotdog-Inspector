#pragma once
#include "Math.hpp"
#include "Sprite.hpp"
#include "Controls.hpp"

// Class to draw a custom cursor to the mouse pos, and 
// also is a Clickable item because it will iteract with Clickables
class Cursor : public Sprite
{
public:
	using Sprite::Sprite;
	void setControls(Controls* p_controls);
	void init();
	void setTarget(const Vector2f* p_target);
	void update(const float& p_dt) override;

	void onCollisionBegin(Sprite* p_sprite) override;
	void onCollisionEnd(Sprite* p_sprite) override;

	Sprite* getSlot();
	void setSlot(Sprite*);

	bool isSlotFull();
private:
	// Vector2f* to the target position, which is the mouse coordinates
	Controls* controls;
	const Vector2f* target;
	Sprite* slot;
	bool slotFull;
};