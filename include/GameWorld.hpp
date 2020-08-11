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
#include "Character.hpp"

// The place where all of the sprites live
class GameWorld
{
public:
	// Destructor
	~GameWorld();
	GameWorld(Controls* p_controls)
	:controls(p_controls) {}

	// Create a camera
	Camera* createCamera(Vector2f p_pos, Vector2f p_size);

	// Create ______ (fill in the blank). The p_drawOrder specifies the layering of the 
	// renderer. A higher p_drawOrder will result in being draw on top of lower p_drawOrder
	Conveyor* createConveyor(SpriteCreateInfo& p_info, int p_drawOrder);
	Sprite* createSprite(SpriteCreateInfo& p_info, int p_drawOrder);
	Particle* createParticle(SpriteCreateInfo& p_info, int p_drawOrder);
	Cursor* createCursor(SpriteCreateInfo& p_info, int p_drawOrder);
	Character* createCharacter(SpriteCreateInfo& p_info, std::string character, int p_drawOrder);

	// Create clickable
	Clickable* createClickable(ClickableCreateInfo& p_info);
	
	// Not in use. The particle system currently isn't operational
	int getNumParticles() {	return particles.size();}

	// Get a reference to all of the Sprites, used when rendering everything
	const std::multimap<int, Sprite*>& getAllSprites();

	// Get a reference to the camera
	const Camera& getCamera();

	// Check if any clickables are colliding
	void clickableTest();

	// Move everything forward in time, by a set amount(dt)
	void update(const double& dt);

	// Not in use.
	// I used to use refresh when I was using Box2D. The refresh method would
	// set the pos of the Sprites to the pos of the Box2D body, if the sprite had a body
	void refresh();
private:
	// The cursor
	Cursor cursor;

	// Ptr to the controls
	Controls* controls;
	std::list<Conveyor> conveyors;
	std::list<Character> characters;

	Camera camera;
	std::list<Sprite> sprites;
	std::vector<Particle*> particles;

	// A ptr to all of the sprites, and all of the objects that inherit the sprite class.
	std::multimap<int, Sprite*> allSprites;

	std::list<Clickable> clickables;
};