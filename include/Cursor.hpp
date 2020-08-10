#pragma once
#include "Math.hpp"
#include "Sprite.hpp"
#include "Clickable.hpp"

class Cursor : public Sprite, public Clickable
{
public:
	using Sprite::Sprite;
	void setTarget(const Vector2f* p_target);
	void update(const float& p_dt) override;
private:
	const Vector2f* target;
};