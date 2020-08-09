#pragma once
#include <list>
#include <vector>
#include <map>

#include "Sprite.hpp"
#include "Math.hpp"
#include "Camera.hpp"
#include "Particle.hpp"

class GameWorld
{
public:
	~GameWorld();
	GameWorld() {}
	void createCamera(Vector2f p_pos, Vector2f p_size);
	void createSprite(SpriteCreateInfo& p_info, int p_drawOrder);
	void createParticle(SpriteCreateInfo& p_info, int p_drawOrder);
	
	int getNumParticles() {	return particles.size();}
	const std::multimap<int, Sprite*>& getAllEntities();
	const Camera& getCamera();
	void update(const double& dt);
	void refresh();
private:
	Camera camera;
	std::list<Sprite> entities;
	std::vector<Particle*> particles;
	std::multimap<int, Sprite*> allEntities;
};