#pragma once

#include "Math.hpp"

class Clickable
{
public:
	Clickable(){}
	Vector2f& getSize() { return size; }

private:
	Vector2f size;
};