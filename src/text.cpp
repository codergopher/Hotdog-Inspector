#include "Text.hpp"

Text::Text(const SpriteCreateInfo& p_info, std::string p_string)
:string(p_string),
info(p_info)
{
	for (Uint8 i = 0; i < string.length(); i++)
	{
		if (string.at(i) != ' ')
		{
			SpriteCreateInfo tempInfo = info;
			tempInfo.pos.x = tempInfo.pos.x + spacing*(i);
			std::string cur; 
			cur += string.at(i); //for some reason I have to do += to get the char into a c++ string
			characters.push_back(Character(tempInfo, cur));
		}
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

void Text::setText(std::string p_string)
{
	for (auto& c : characters)
	{
<<<<<<< HEAD
		std::string cur; 
		cur += p_string.at(i);
		//characters.at(i).setCharacter(cur);
		characters.at(i).setCharacter("1");
=======
		// std::string cur; 
		// cur += p_string.at(i);
		//c.setCharacter("g");
>>>>>>> ccf3993bae31fe14029b2f8be53286f50dc95dc2
	}
}

