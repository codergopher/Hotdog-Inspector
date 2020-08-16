#include "Conveyor.hpp"
#include "Cursor.hpp"
Conveyor::Conveyor() {}

Conveyor::Conveyor(const SpriteCreateInfo& p_info)
:Sprite::Sprite(p_info),
speed(0.1f, 0.0f)
{
	
	loadFrames(frameSize);
	currentFrame = frames[0];

	// Set the playback speed of the main animation
	animationSet["Conveyor"].playBackSpeed = 0.2f;
}

void Conveyor::update(const float& p_dt)
{
	speed.x += 0.001f;
//	animationSet["Conveyor"].playBackSpeed += 0.001f;
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