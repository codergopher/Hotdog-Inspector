#include "Menu.hpp"
#include "Cursor.hpp"
Menu::Menu() {}

Menu::Menu(const SpriteCreateInfo& p_info)
:Sprite::Sprite(p_info)
{
	
	loadFrames(frameSize);
	currentFrame = frames[0];

}

void Menu::update(const float& p_dt)
{
	//play(animationSet["main"]);
}
