#pragma once

#include "Math.hpp"

// Quick little struct to create parameters
// for the clickable
struct ClickableCreateInfo
{	
	ClickableCreateInfo()
	:pos(0.0f, 0.0f),
	posPtr(nullptr),
	halfSize(0.0f, 0.0f),
	ptr(nullptr)
	{

	}
	Vector2f pos;
	Vector2f* posPtr;
	Vector2f halfSize;
	void* ptr;
};

// A clickable is anything that can interact with the cursor
class Clickable
{
public:
	Clickable(){}
	Clickable(ClickableCreateInfo& p_info)
	:pos(p_info.pos),
	posPtr(p_info.posPtr),
	halfSize(p_info.halfSize),
	ptr(p_info.ptr)
	{}

	const Vector2f& getPos() const { return pos; }
	const Vector2f* getPosPtr() const { return posPtr; } 
	const Vector2f& getHalfSize() const { return halfSize; }

	void setPos(const Vector2f& p_pos) { pos = p_pos; }
	void setPosPtr(Vector2f* p_posPtr) { posPtr = p_posPtr; }
	void setHalfSize(const Vector2f& p_halfSize) { halfSize = p_halfSize; }

	void update(const float& p_dt)
	{
		// If the position of this Clickable is actually the position of
		// a sprite or something, then update this clickable's pos to be that sprite pos
		if (posPtr != nullptr)
		{
			pos = (*posPtr);
		}
	}

private:
	Vector2f pos;
	Vector2f* posPtr;
	Vector2f halfSize;

	void* ptr;
};

// Method to determine if two clickables are colliding
inline bool ClickableVsClickable(const Clickable& p_a, const Clickable& p_b)
{

	Vector2f delta = p_b.getPos() - p_a.getPos();
	Vector2f totalSize = p_b.getHalfSize() + p_a.getHalfSize();

	if (abs(delta.x) < totalSize.x &&
		abs(delta.y) < totalSize.y)
	{	

		return true;
	}

	return false;
}