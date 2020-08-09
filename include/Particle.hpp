#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Sprite.hpp"

class Particle : public Sprite
{
public:
	Particle() {}
	Particle(const SpriteCreateInfo& p_info);

	void update(const float& p_dt) override;

private:
	float fAlpha = 255;
	float scaleLifeTime = 10.f;
	float alphaLifeTime = 300.f;	
};

class ParticleSource
{

};
