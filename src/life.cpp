#include "Life.hpp"

Life::Life() {}

Life::Life(const SpriteCreateInfo& p_info)
{
	name = p_info.name;
	tex = p_info.tex;
	color = p_info.color;
	alpha = p_info.alpha;
	flip = p_info.flip;
	prevPos = p_info.pos,
	pos = p_info.pos;
	angle = p_info.angle;
	origin = p_info.origin;
	frameSize = p_info.frameSize;
	scale = p_info.scale;
	depth = p_info.depth;
	zoomModifier = p_info.zoomModifier;
	
	loadFrames(frameSize);
	currentFrame = frames[0];

	// Load a set of Animation Cycles from a file
	animationSet = loadAnimationFile("res/UI/X.json");
	// Set the playback speed of the main animation
	animationSet["Enabled"].playBackSpeed = 1.f;
	animationSet["Disabled"].playBackSpeed = 1.f;
}

void Life::update(const float& p_dt)
{

	animate(p_dt);
	
}

void Life::updateIcon(bool p_value)
{
	icon = p_value;
}

void Life::animate(const float& p_dt)
{
	if (icon)
	{
		play(animationSet["Enabled"]);
	}
	else
	{
		play(animationSet["Disabled"]);
	}
}