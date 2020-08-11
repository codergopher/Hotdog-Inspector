#include "Text.hpp"

Text::Text(const SpriteCreateInfo& p_info, std::string p_string)
:info(p_info), string(p_string)
{
	for (Uint8 i = 0; i < string.length(); i++)
	{
		SpriteCreateInfo tempInfo = info;
		tempInfo.pos.x = tempInfo.pos.x + spacing*(i);
		std::string cur; 
		cur += string.at(i); //for some reason I have to do += to get the char into a c++ string
		characters.push_back(Character(tempInfo, cur));
	}
}

Character& Text::getCharacter(Uint8 p_index)
{
	return characters.at(p_index);
}

Uint8 Text::getSize()
{
	return characters.size();
}
