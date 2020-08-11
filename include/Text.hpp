#pragma once

#include <map>
#include <string>

#include "Math.hpp"
#include "Character.hpp"

class Text
{
public:
	Text();
	Text(const SpriteCreateInfo& p_info, std::string p_string);
	Character& getCharacter(Uint8 p_index);
	Uint8 getSize();
	//void update(const float& p_dt) override;

private:
	Uint8 spacing = 5;
	std::string string;
	std::vector<Character> characters;
	const SpriteCreateInfo& info; //to be passed to the character, I don't really need to store this right now but it might be useful for updating text position mid-game or something
};