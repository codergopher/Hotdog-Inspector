#pragma once

#include "Sprite.hpp"
#include "Animation.hpp"
#include "Lives.hpp"

class Hotdog : public Sprite
{
public:
	Hotdog();
	Hotdog(const SpriteCreateInfo& p_info, Lives* p_lifeCounter);

	void update(const float& p_dt) override;

	void onCollisionBegin(Sprite* p_sprite) override;
	void duringCollision(Sprite* p_sprite) override;
	void onCollisionEnd(Sprite* p_sprite) override;

	bool isCanKill() { return canKill; }
private:


	bool canKill;
	bool isDying;

	float fAlpha;
	float scaleLifeTime;
	float alphaLifeTime;

<<<<<<< HEAD
	Lives* lifeCounter;

	Vector2f targetPos;
=======
	Vector2f* targetPos;
	Vector2f lastTargetPos;
>>>>>>> a34f7444bd6dad1b10b13d4dd48345a1c53fc223

	float lag;
};