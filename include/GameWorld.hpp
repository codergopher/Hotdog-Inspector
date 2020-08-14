#pragma once
#include <list>
#include <vector>
#include <map>
#include <set>

#include <memory>

#include "Sprite.hpp"
#include "Math.hpp"
#include "Camera.hpp"
#include "Conveyor.hpp"
#include "Particle.hpp"
#include "Controls.hpp"
#include "Cursor.hpp"
#include "Character.hpp"
#include "Text.hpp"
#include "Hotdog.hpp"
#include "Crate.hpp"

struct CollisionInfo
{
	Sprite* a;
	Sprite* b;

	// Mutable so that we can this var is changeable in 
	// a const context.
	mutable int framesLeft;
	mutable bool freshCollision;

	bool contains(Sprite* p_sprite);
};

bool operator ==(CollisionInfo& p_a, CollisionInfo& p_b);

// The place where all of the sprites live
class GameWorld
{
public:
	// Destructor
	~GameWorld();
	GameWorld(){}
	GameWorld(Controls* p_controls);

	// Create the clickable structs
	void createClickableData(std::map<std::string, SDL_Texture*> p_textures);

	// Create a camera
	Camera* createCamera(Vector2f p_pos, Vector2f p_size);

	// Create ______ (fill in the blank). The p_drawOrder specifies the layering of the 
	// renderer. A higher p_drawOrder will result in being draw on top of lower p_drawOrder
	Crate* createCrate(SpriteCreateInfo& p_info, int p_drawOrder);
	Conveyor* createConveyor(SpriteCreateInfo& p_info, int p_drawOrder);
	Sprite* createSprite(SpriteCreateInfo& p_info, int p_drawOrder);
	Particle* createParticle(SpriteCreateInfo& p_info, int p_drawOrder);
	Cursor* createCursor(SpriteCreateInfo& p_info, int p_drawOrder);

	Character* createCharacter(SpriteCreateInfo& p_info, std::string character, int p_drawOrder);

	Text* createText(SpriteCreateInfo& p_info, std::string string, int p_drawOrder);

	Hotdog* createHotdog(SpriteCreateInfo& p_info, int p_drawOrder);

	void deleteSprite(Sprite* sprite);
	
	// Not in use. The particle system currently isn't operational
	int getNumParticles() {	return particles.size();}

	// Get a reference to all of the Sprites, used when rendering everything
	const std::multimap<int, Sprite*>& getAllSprites();

	// Get a reference to the camera
	const Camera& getCamera();

	bool SpriteVsSprite(Sprite* p_a, Sprite* p_b);

	// Check if any clickables are colliding
	void collisionTest();

	void resolveCollision(Sprite* p_a, Sprite* p_b);

	void updateCollisions();

	// Move everything forward in time, by a set amount(dt)
	void update(const double& dt, std::map<std::string, SDL_Texture*> textures);
private:
	 //for moving clickables
    float moveSpeed = .1f;


	// The cursor
	Cursor* cursor;

	// Ptr to the controls
	Controls* controls;
	std::vector<Crate*> crates;
	std::vector<Conveyor*> conveyors;
	std::list<Text> texts;
	std::list<Character> characters;


	Camera camera;
	std::vector<Sprite*> sprites;
	std::vector<Particle*> particles;
	std::vector<Hotdog*> hotdogs;

	// A ptr to all of the sprites, and all of the objects that inherit the sprite class.
	std::multimap<int, Sprite*> allSprites;

	// A set of all of the collisions.
	// std::set ensures that there are only unique collisions
	std::list<CollisionInfo> allCollisions;

	int collisionFrames;

	    //for spawning clickables
	std::vector<SpriteCreateInfo> clickables;
    float timer = 100;
	
    int dawgs;
};