#include <iostream>
#include <algorithm>

#include "GameWorld.hpp"
#include "Sprite.hpp"
#include "Camera.hpp"
#include "Particle.hpp"

extern int gWinWidth;
extern int gWinHeight;

GameWorld::~GameWorld()
{
	for (Particle* p : particles)
	{
		delete p;
	}
}


void GameWorld::createCamera(Vector2f p_pos, Vector2f p_size)
{
	CameraCreateInfo createInfo = {};
	createInfo.pos = p_pos;
	createInfo.size = p_size;
	createInfo.zoom = 3;
	createInfo.lag = 0.08f;
	camera = Camera(createInfo);
	camera.init();
}

void GameWorld::createSprite(SpriteCreateInfo& p_info, int p_drawOrder)
{
	

	Sprite e(p_info);
	entities.push_back(e);

	allEntities.insert(std::pair<int, Sprite*>(p_drawOrder, &entities.back()));
}

void GameWorld::createParticle(SpriteCreateInfo& p_info, int p_drawOrder)
{
	Particle* p = new Particle(p_info);

	particles.push_back(p);

	allEntities.insert(std::pair<int, Sprite*>(p_drawOrder, particles.back()));
}


const std::multimap<int, Sprite*>& GameWorld::getAllEntities()
{
	return allEntities;
}

const Camera& GameWorld::getCamera()
{
	return camera;
}


void GameWorld::update(const double& dt)
{
	camera.updatePrev();
	camera.update(Vector2f(0.0f, 0.0f));

	for (std::multimap<int, Sprite*>::iterator i = allEntities.begin(); i != allEntities.end(); ++i)
	{
		Sprite* e = i->second;

		// if (e->shouldDelete())
		// {	
		// 	if (e->getName() == "Particle")
		// 	{

		// 		//std::cout << "haha, going to delete this lol" << std::endl;
		// 		std::vector<Particle*>::iterator p = std::find(particles.begin(), particles.end(), (Particle*)e);

		// 		PhysicsObject* physicsObject = e->getPhysicsObject();

		// 		if (physicsObject != nullptr)
		// 			physics->deleteObject(physicsObject);

		// 		delete e;
		// 		particles.erase(p);
		// 		allEntities.erase(i);
		// 		continue;
		// 	}
		// }
		e->updatePrev();
		e->update(dt);
	}
}

void GameWorld::refresh()
{
	// for (std::multimap<int, Sprite*>::iterator i = allEntities.begin(); i != allEntities.end(); ++i)
	// {
	// 	Sprite* e = i->second;
	// 	//not needed
	// }
}