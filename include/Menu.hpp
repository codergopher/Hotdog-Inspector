#pragma once

#include <map>
#include <string>

#include "Sprite.hpp"
#include "Animation.hpp"

class Menu : public Sprite
{
public:
	Menu();
	Menu(const SpriteCreateInfo& p_info);

	void update(const float& p_dt) override;

private:
};