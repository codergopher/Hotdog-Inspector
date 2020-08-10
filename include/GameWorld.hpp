#pragma once
#include <list>
#include <vector>
#include <map>

#include "Sprite.hpp"
#include "Math.hpp"
#include "Camera.hpp"
#include "Conveyor.hpp"
#include "Particle.hpp"
#include "Controls.hpp"
#include "Cursor.hpp"

class GameWorld
{
public:
	~GameWorld();
	GameWorld(Controls* p_controls)
	:controls(p_controls) {}
	void createCamera(Vector2f p_pos, Vector2f p_size);
	void createConveyor(SpriteCreateInfo& p_info, int p_drawOrder);
	void createSprite(SpriteCreateInfo& p_info, int p_drawOrder);
	void createParticle(SpriteCreateInfo& p_info, int p_drawOrder);

	Cursor* createCursor(SpriteCreateInfo& p_info, int p_drawOrder);
	
	int getNumParticles() {	return particles.size();}
	const std::multimap<int, Sprite*>& getAllEntities();
	const Camera& getCamera();
	void update(const double& dt);
	void refresh();
private:
	Cursor cursor;
	Controls* controls;
	std::list<Conveyor> conveyors;
	Camera camera;
	std::list<Sprite> entities;
	std::vector<Particle*> particles;
	std::multimap<int, Sprite*> allEntities;
};