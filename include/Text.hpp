#pragma once

#include <SDL2/SDL_ttf.h>
#include "Sprite.hpp"

class Text : public Sprite
{
public:
	Text();
	Text(const SpriteCreateInfo& p_info, const char* p_string);

	void update(const float& p_dt) override;
	void setText(const char* p_string);

private:
	
};