#include "Player.hpp"
#include "Math.hpp"
#include <iostream>

extern bool gKeys[4];

Player::Player() {}

Player::Player(const SpriteCreateInfo& p_info)

{
	name = p_info.name;
	tex = p_info.tex;
	color = p_info.color;
	alpha = p_info.alpha;
	flip = p_info.flip;
	prevPos = p_info.pos,
	pos = p_info.pos;
	origin = p_info.origin;
	frameSize = p_info.frameSize;
	scale = p_info.scale;
	depth = p_info.depth;
	zoomModifier = p_info.zoomModifier;
    body = p_info.body;
	
	loadFrames(frameSize);
	currentFrame = frames[0];

	animationSet = loadAnimationFile("res/humans/buckland_0.json");
	animationSet["idle"].playBackSpeed = 3.0f;
}

void Player::update(const float& p_dt)
{
	if (gKeys[W])
		body->ApplyForce(b2Vec2(0, -5), body->GetWorldCenter(), true);
	if (gKeys[A])
		body->ApplyForce(b2Vec2(-5, 0), body->GetWorldCenter(), true);
	if (gKeys[S])
		body->ApplyForce(b2Vec2(0, 5), body->GetWorldCenter(), true);
	if (gKeys[D])
		body->ApplyForce(b2Vec2(5, 0), body->GetWorldCenter(), true);

	animate(p_dt);
}

void Player::animate(const float& p_dt)
{
	if (abs(body->GetLinearVelocity().x) > 0.7f )
		play(animationSet["walk"]);
	else
		play(animationSet["idle"]);
}
