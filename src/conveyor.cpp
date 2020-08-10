#include "Conveyor.hpp"

Conveyor::Conveyor() {}

Conveyor::Conveyor(const SpriteCreateInfo& p_info)

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
