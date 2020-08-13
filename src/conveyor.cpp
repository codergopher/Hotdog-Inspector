#include "Conveyor.hpp"
#include "Cursor.hpp"
Conveyor::Conveyor() {}

Conveyor::Conveyor(const SpriteCreateInfo& p_info)
:Sprite::Sprite(p_info)
{
	
	loadFrames(frameSize);
	currentFrame = frames[0];

	// Load a set of Animation Cycles from a file
	animationSet = loadAnimationFile("res/conveyor_belt_0.json");
	// Set the playback speed of the main animation
	animationSet["Conveyor"].playBackSpeed = 0.2f;
}

void Conveyor::update(const float& p_dt)
{

	animate(p_dt);
}

void Conveyor::animate(const float& p_dt)
{
	// This is where we would have the logic for when animations
	// should happen
	play(animationSet["Conveyor"]);
}

void Conveyor::onCollisionBegin(Sprite* p_sprite)
{

}