#pragma once
#include "Math.hpp"
#include "Sprite.hpp"

// Class to draw a custom cursor to the mouse pos, and 
// also is a Clickable item because it will iteract with Clickables
class Cursor : public Sprite
{
public:
	using Sprite::Sprite;
	void setTarget(const Vector2f* p_target);
	void update(const float& p_dt) override;
private:
	// Vector2f* to the target position, which is the mouse coordinates
	const Vector2f* target;
};