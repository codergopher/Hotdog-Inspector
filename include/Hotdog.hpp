#pragma once

#include "Sprite.hpp"
#include "Animation.hpp"
#include "Lives.hpp"
#include "AudioManager.hpp"
extern bool quit;

class Hotdog : public Sprite
{
public:
	Hotdog();
	Hotdog(const SpriteCreateInfo& p_info, Lives* p_lifeCounter, AudioManager* p_audioManager);

	void update(const float& p_dt) override;

	void onCollisionBegin(Sprite* p_sprite) override;
	void duringCollision(Sprite* p_sprite) override;
	void onCollisionEnd(Sprite* p_sprite) override;

	bool isCanKill() { return canKill; }

	void animate(const float& p_dt);
private:
	bool playedSound = false;
	bool atLastTarget;

	bool canKill;
	bool isDying;

	float fAlpha;
	float scaleLifeTime;
	float alphaLifeTime;

	Lives* lifeCounter;
	

	Vector2f* targetPos;
	Vector2f lastTargetPos;

	float lag;

	AudioManager* audioManager;
};