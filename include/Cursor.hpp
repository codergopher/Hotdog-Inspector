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
	void update(const float& p_dt) override;

	void onCollisionBegin(Sprite* p_sprite) override;
	void onCollisionEnd(Sprite* p_sprite) override;

	Sprite* getSlot();

	
	void setSlot(Sprite*);

	bool isSlotFull();
private:
	// Ptr to the controls, to set the cursor to be
	// the mouse position
	Controls* controls;

	// The sprite that is currently grabbed by the
	// cursor
	Sprite* slot;

	// Is the slot full or empty?
	bool slotFull;
};