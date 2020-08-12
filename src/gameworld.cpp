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

bool operator ==(CollisionInfo& p_a, CollisionInfo& p_b)
{
	size_t hashA = (size_t)p_a.a + (size_t)p_a.b;
	size_t hashB = (size_t)p_b.a + (size_t)p_b.b;

	if (hashA == hashB)
		return true;

	return false;
}

GameWorld::~GameWorld()
{
	// Delete any particles that haven't been deleted
	for (Particle* p : particles)
	{
		delete p;
	}
}

// create the camera, pretty simple
Camera* GameWorld::createCamera(Vector2f p_pos, Vector2f p_size)
{
	CameraCreateInfo createInfo = {};
	createInfo.pos = p_pos;
	createInfo.size = p_size;
	createInfo.zoom = 8;
	createInfo.lag = 0.08f;
	camera = Camera(createInfo);
	return &camera;
}

// p_drawOrder is the drawing heiarchy
Conveyor* GameWorld::createConveyor(SpriteCreateInfo& p_info, int p_drawOrder)
{
	Conveyor c(p_info);
	conveyors.push_back(c);

	allSprites.insert(std::pair<int, Sprite*>(p_drawOrder, &conveyors.back()));

	return &conveyors.back();
}


Sprite* GameWorld::createSprite(SpriteCreateInfo& p_info, int p_drawOrder)
{
	
	Sprite e(p_info);
	sprites.push_back(e);

	allSprites.insert(std::pair<int, Sprite*>(p_drawOrder, &sprites.back()));

	return &sprites.back();
}

// Create a particle on the heap
Particle* GameWorld::createParticle(SpriteCreateInfo& p_info, int p_drawOrder)
{
	Particle* p = new Particle(p_info);

	particles.push_back(p);

	allSprites.insert(std::pair<int, Sprite*>(p_drawOrder, particles.back()));

	return p;
}

Cursor* GameWorld::createCursor(SpriteCreateInfo& p_info, int p_drawOrder)
{
	cursor = Cursor(p_info);
	cursor.setTarget(controls->getWorldMousePos());

	allSprites.insert(std::pair<int, Sprite*>(p_drawOrder, &cursor));

	return &cursor;
}

Character* GameWorld::createCharacter(SpriteCreateInfo& p_info, std::string character, int p_drawOrder)
{
	Character c(p_info, character);
	characters.push_back(c);

	allSprites.insert(std::pair<int, Sprite*>(p_drawOrder, &characters.back()));

	return &characters.back();
}

Text* GameWorld::createText(SpriteCreateInfo& p_info, std::string string, int p_drawOrder)
{
	Text c(p_info, string);

	for (int i = 0; i < c.getSize(); i++)
	{
		characters.push_back(c.getCharacter(i));
		allSprites.insert(std::pair<int, Sprite*>(p_drawOrder, &characters.back()));
	}

	texts.push_back(c);
	return &texts.back();
}


const std::multimap<int, Sprite*>& GameWorld::getAllSprites()
{
	return allSprites;
}

const Camera& GameWorld::getCamera()
{
	return camera;
}

// Method to determine if two clickables are colliding
bool GameWorld::SpriteVsSprite(Sprite* p_a, Sprite* p_b)
{

	Vector2f delta = p_b->getPos() - p_a->getPos();
	Vector2f totalSize = p_b->getHalfBounds() + p_a->getHalfBounds();

	if (abs(delta.x) < totalSize.x &&
		abs(delta.y) < totalSize.y)
	{	

		return true;
	}

	return false;
}

void GameWorld::collisionTest()
{
	std::multimap<int, Sprite*>::iterator first = allSprites.begin();
	std::multimap<int, Sprite*>::iterator last = allSprites.end();

	for (auto a = first; a != last; ++a)
	{
		for (auto b = std::next(a, 1); b != last; ++b)
		{	
			Sprite* x = a->second;
			Sprite* y = b->second;
			if (&x == &y)
			{
				continue;
			}

			if (x->isClickable() != true)
			{
				continue;
			}

			if (y->isClickable() != true)
			{
				continue;
			}

			if (SpriteVsSprite(x, y))
			{
				CollisionInfo collision = {x, y};

				collision.freshCollision = true;
				collision.framesLeft = collisionFrames;

				bool duplicate = false;
				for (CollisionInfo& otherCollision : allCollisions)
				{
					if (collision == otherCollision)
					{
						duplicate = true;
						otherCollision.freshCollision = false;
						otherCollision.framesLeft = collisionFrames;

					}
				}
				if (!duplicate) 
				{
					allCollisions.push_back(collision);
				}


				resolveCollision(x, y);
			}
		}
	}
}

void GameWorld::resolveCollision(Sprite* p_a, Sprite* p_b)
{	
	// Vector2f posA = p_a->getPos();
	// Vector2f posB = p_b->getPos();

	// Vector2f delta = posB - posA;

	// float deltaLength = delta.length();
	// Vector2f normal = normalise(delta);

	// Vector2f correction = normal * deltaLength;

	if (controls->isLeftClick())
	{


		Cursor* cursor = dynamic_cast<Cursor*>(p_a);

		if(cursor)
		{
			if (!cursor->isSlotFull())
				cursor->setSlot(p_b);
		}

	

		cursor = dynamic_cast<Cursor*>(p_b);

		if (cursor)
		{	
			if (!cursor->isSlotFull())
				cursor->setSlot(p_a);
		}

		
	}
}
void GameWorld::updateCollisions()
{	
	for (std::list<CollisionInfo>::iterator i = allCollisions.begin(); i != allCollisions.end(); )
	{
		if ((*i).freshCollision == true)
		{
			i->a->onCollisionBegin(i->b);
			i->b->onCollisionBegin(i->a);
		}

		(*i).framesLeft = (*i).framesLeft - 1;

		if ((*i).framesLeft < 0)
		{
			i->a->onCollisionEnd(i->b);
			i->b->onCollisionEnd(i->a);

			i = allCollisions.erase(i);
		}

		++i;

	}
}

void GameWorld::update(const double& dt)
{
	camera.updatePrev();
	camera.update(Vector2f(0.0f, 0.0f));

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

	//Check for collisions
	collisionTest();

	// Delete old collisions
	updateCollisions();
}
