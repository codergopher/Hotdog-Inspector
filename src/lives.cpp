#include "Lives.hpp"

Lives::Lives(const SpriteCreateInfo& p_info, Uint8 p_lives)
:lives(p_lives),
spacing(8)
{
	// Load a set of Animation Cycles from a file
	animationSet = loadAnimationFile("romfs:/UI/X.json");
	for (Uint8 i = 0; i < lives; i++)
	{
			SpriteCreateInfo tempInfo = p_info;
			tempInfo.pos.x = tempInfo.pos.x + spacing*(i);
			UIsprites.push_back(Sprite(tempInfo));
			// Set the playback speed of the main animation
			animationSet["Enabled"].playBackSpeed = 1.f;
			animationSet["Disabled"].playBackSpeed = 1.f;
	}

	
}

bool Lives::updateLives(Uint8 p_lives)
{
	lives = p_lives;
	//update actual sprites
	for (int i = 0; i < 4 - lives; i++)
	{
		UIsprites.at(i).play(animationSet["Enabled"]);

	}
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
