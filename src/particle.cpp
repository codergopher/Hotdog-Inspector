#include "Particle.hpp"
#include "Math.hpp"
#include <iostream>

Particle::Particle(const SpriteCreateInfo& p_info)
{
	name = p_info.name;
	tex = p_info.tex;
	color = p_info.color;
	alpha = p_info.alpha;
	fAlpha = alpha;
	flip = p_info.flip;
	prevPos = p_info.pos,
	pos = p_info.pos;
	origin = p_info.origin;
	frameSize = p_info.frameSize;
	scale = p_info.scale;
	angle = p_info.angle;
	depth = p_info.depth;
	zoomModifier = p_info.zoomModifier;
	body = p_info.body;
	
	loadFrames(frameSize);
	currentFrame = frames[0];
}

void Particle::update(const float& p_dt)
{
	scale += scaleLifeTime * p_dt;


	if (alpha > 0)
	{
		fAlpha -= alphaLifeTime * p_dt;
		alpha = roundToInt(fAlpha);
	}
	else
	{
		pleaseDelete = true;
	}
}
