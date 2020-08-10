#include <iostream>
#include <algorithm>

#include "Conveyor.hpp"
#include "GameWorld.hpp"
#include "Sprite.hpp"
#include "Camera.hpp"
#include "Particle.hpp"
#include "Cursor.hpp"

extern int gWinWidth;
extern int gWinHeight;

GameWorld::~GameWorld()
{
	// Delete any particles that haven't been deleted
	for (Particle* p : particles)
	{
		delete p;
	}
}

// create the camera, pretty simple
void GameWorld::createCamera(Vector2f p_pos, Vector2f p_size)
{
	CameraCreateInfo createInfo = {};
	createInfo.pos = p_pos;
	createInfo.size = p_size;
	createInfo.zoom = 8;
	createInfo.lag = 0.08f;
	camera = Camera(createInfo);
}

// p_drawOrder is the drawing heiarchy
void GameWorld::createConveyor(SpriteCreateInfo& p_info, int p_drawOrder)
{
	Conveyor c(p_info);
	conveyors.push_back(c);

	allSprites.insert(std::pair<int, Sprite*>(p_drawOrder, &conveyors.back()));
}


void GameWorld::createSprite(SpriteCreateInfo& p_info, int p_drawOrder)
{
	
	Sprite e(p_info);
	sprites.push_back(e);

	allSprites.insert(std::pair<int, Sprite*>(p_drawOrder, &sprites.back()));
}

// Create a particle on the heap
void GameWorld::createParticle(SpriteCreateInfo& p_info, int p_drawOrder)
{
	Particle* p = new Particle(p_info);

	particles.push_back(p);

	allSprites.insert(std::pair<int, Sprite*>(p_drawOrder, particles.back()));
}

void GameWorld::createCursor(SpriteCreateInfo& p_info, int p_drawOrder)
{
	cursor = Cursor(p_info);
	cursor.setTarget(controls->getWorldMousePos());

	allSprites.insert(std::pair<int, Sprite*>(p_drawOrder, &cursor));
}



const std::multimap<int, Sprite*>& GameWorld::getAllSprites()
{
	return allSprites;
}

const Camera& GameWorld::getCamera()
{
	return camera;
}


void GameWorld::update(const double& dt)
{
	camera.updatePrev();
	camera.update(Vector2f(0.0f, 0.0f));

	//controls->printState();

	// Iterate through all of the sprites and update them
	// NOTE: Should have an Entity class and then only update Entities
	for (std::multimap<int, Sprite*>::iterator i = allSprites.begin(); i != allSprites.end(); ++i)
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
		// 		allSprites.erase(i);
		// 		continue;
		// 	}
		// }
		e->updatePrev();
		e->update(dt);
	}
}

void GameWorld::refresh()
{
	// for (std::multimap<int, Sprite*>::iterator i = allSprites.begin(); i != allSprites.end(); ++i)
	// {
	// 	Sprite* e = i->second;
	// 	//not needed
	// }
}