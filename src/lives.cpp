#include "Lives.hpp"

Lives::Lives(const SpriteCreateInfo& p_info, Uint8 p_lifeCount)
:lifeCount(p_lifeCount),
spacing(8)
{
	// Load a set of Animation Cycles from a file
	animationSet = loadAnimationFile("res/UI/X.json");
	for (Uint8 i = 0; i < lifeCount; i++)
	{
			SpriteCreateInfo tempInfo = p_info;
			tempInfo.pos.x = tempInfo.pos.x + spacing*(i);
			lives.push_back(Life(tempInfo));
			// Set the playback speed of the main animation
			animationSet["Enabled"].playBackSpeed = 1.f;
			animationSet["Disabled"].playBackSpeed = 1.f;
	}

	
}

bool Lives::updateLives(Uint8 p_lifeCount)
{
	lifeCount = p_lifeCount;
	//update actual sprites
	for (int i = 0; i < 4 - lifeCount; i++)
	{
		lives.at(i).updateIcon(true);
	}
	return lifeCount > 0; //will return false if u r dead
}

bool Lives::removeLife()
{
	return updateLives(lifeCount - 1);
}

Uint8 Lives::getLifeCount()
{
	return lifeCount;
}

Sprite& Lives::getLives(Uint8 p_index)
{
	return lives.at(p_index);
}
