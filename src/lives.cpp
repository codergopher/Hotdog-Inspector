#include "Lives.hpp"

Lives::Lives(const SpriteCreateInfo& p_info, Uint8 p_lives)
:lives(p_lives)
{
	for (Uint8 i = 0; i < lives; i++)
	{
			std::cout << "ok" << std::endl;
			SpriteCreateInfo tempInfo = p_info;
			tempInfo.pos.x = tempInfo.pos.x + spacing*(i);
			UIsprites.push_back(Sprite(tempInfo));
	}
}

bool Lives::updateLives(Uint8 p_lives)
{
	lives = p_lives;
	//update actual sprites
	return lives > 0; //will return false if u r dead
}

bool Lives::removeLife()
{
	return updateLives(lives - 1);
}

Uint8 Lives::getLives()
{
	return lives;
}

Sprite& Lives::getSprite(Uint8 p_index)
{
	return UIsprites.at(p_index);
}
