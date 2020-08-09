#pragma once
#include <list>
#include <vector>
#include <map>

#include <Box2D/Box2D.h>

#include "Sprite.hpp"
#include "Player.hpp"
#include "Math.hpp"
#include "Camera.hpp"
#include "Particle.hpp"

class GameWorld
{
public:
	~GameWorld();
	GameWorld() {}
	GameWorld(b2World* p_physics);
	void createCamera(Vector2f p_pos, Vector2f p_size);
	void createPlayer(SpriteCreateInfo& p_info, int p_drawOrder);
	void createSprite(SpriteCreateInfo& p_info, int p_drawOrder);
	void createParticle(SpriteCreateInfo& p_info, int p_drawOrder);
	
	int getNumParticles() {	return particles.size();}
	const std::multimap<int, Sprite*>& getAllEntities();
	const Camera& getCamera();
	void update(const double& dt);
	void refresh();
private:
	Camera camera;
	Player player;
	std::list<Sprite> entities;
	std::vector<Particle*> particles;
	std::multimap<int, Sprite*> allEntities;

	b2World* physics;
};