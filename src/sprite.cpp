#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>

#include "Sprite.hpp"
#include "Math.hpp"

extern float* gCameraZoom;

SpriteCreateInfo::SpriteCreateInfo()
:
name(""),
tex(NULL), 
color(255, 255, 255),
src({0, 0, 0, 0}),
dst({0, 0, 0, 0}),
alpha(255), 
flip(SDL_FLIP_NONE), 
pos(0, 0), 
origin(0, 0), 
frameSize(0, 0), 
scale(1, 1), 
angle(0),
prevAngle(0.f),
depth(1), 
zoomModifier(0), 
body(nullptr)
{}



Sprite::~Sprite() 
{
	//std::cout << "Deleted " << name << std::endl;
	if (body != nullptr)
	{

	}
}

Sprite::Sprite(const SpriteCreateInfo& p_info)
:
name(p_info.name),
tex(p_info.tex),
color(p_info.color),
alpha(p_info.alpha),
flip(p_info.flip),
prevPos(p_info.pos),
pos(p_info.pos),
origin(p_info.origin),
frameSize(p_info.frameSize),
scale(p_info.scale),
angle(p_info.angle),
depth(p_info.depth),
zoomModifier(p_info.zoomModifier),
body(p_info.body)
{

	loadFrames(frameSize);
	currentFrame = frames[0];
}

void Sprite::setPos(Vector2f p_pos)
{	
	pos = p_pos;
}

void Sprite::setScale(Vector2f p_scale)
{
	scale = scale;
}

void Sprite::loadFrames(Vector2i p_size)
{
	Vector2i tSize;
	SDL_QueryTexture(tex, NULL, NULL, &tSize.x, &tSize.y);

	Vector2i framesAmount;
	framesAmount = tSize / p_size;

	for(int y = 0; y < framesAmount.y; y++)
	{
		for(int x = 0; x < framesAmount.x; x++)
		{
			Frame frame(IntRect(x*p_size.x, y*p_size.y, p_size.x, p_size.y), 100, tex);
			frames.push_back(frame);
		}
	}
}

void Sprite::updatePrev()
{
	prevPos = pos;
	prevAngle = angle;
}

void Sprite::update(const float& p_dt)
{

}

void Sprite::play(AnimationCycle& p_cycle)
{
	p_cycle.delta += 10;

	if (p_cycle.delta >= p_cycle.frames[p_cycle.currentFrame].duration / p_cycle.playBackSpeed)
	{

		p_cycle.currentFrame++;

		if(p_cycle.currentFrame >= p_cycle.frames.size())
			p_cycle.currentFrame = 0;

		p_cycle.delta = 0;

		currentFrame = p_cycle.frames[p_cycle.currentFrame];
	}
}