#pragma once

#include "Math.hpp"

// A clickable is anything that can interact with the cursor
class Clickable
{
public:
	Clickable(){}
	Vector2f& getSize() { return size; }

private:
	Vector2f size;
};