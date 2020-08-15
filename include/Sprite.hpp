#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <string>

#include "Math.hpp"
#include "Animation.hpp"

// A simple Colour structure. For simplicity, I have called it
// Color instead of Colour(much to my chagrin)
struct Color
{
	int r;
	int g;
	int b;

	Color()
	:
	r(255),
	g(255),
	b(255)
	{
	}

	Color(int p_r, int p_g, int p_b)
	:
	r(p_r),
	g(p_g),
	b(p_b)
	{		
	}
};

// A struct to supply a sprite with parameters
struct SpriteCreateInfo
{
	SpriteCreateInfo();
	std::string name;
	SDL_Texture* tex;
	Color color;
	SDL_Rect src;
	SDL_Rect dst;
	Uint8 alpha;
	SDL_RendererFlip flip;
	Vector2f pos;
	Vector2f origin;
	Vector2i frameSize;
	Vector2f scale;
	float angle;
	float prevAngle;
	float depth;
	float zoomModifier;

	bool clickable;
	bool interactsWithCursor;
	Vector2f halfBounds;
};

// The basic unit that can be rendered
class Sprite
{
public:

	Sprite(){}
	Sprite(const SpriteCreateInfo& p_info);

	// A virtual destructor, in case sub classes wish
	// to have their own destructor definition
	virtual ~Sprite();

	// Should this Sprite be deleted?
	// Useful if the Sprite was created with the new keyword
	bool shouldDelete() const { return pleaseDelete; }

	void mustDelete(bool should) { pleaseDelete = should; }

	// Pretty straight forward here
	const std::string& getName() const { return name; }

	SDL_Texture* getTex() const { return tex; }

	Color getColor()  { return color; }

	const Uint8& getAlpha() const { return alpha; }

	const SDL_RendererFlip& getFlip() const { return flip; }

	const SDL_Rect& getSrc() const { return src; }

	const SDL_Rect& getDst() const { return dst; }

	const Vector2f& getPrevPos() const {return prevPos; }

	Vector2f& getPos() { return pos; }

	Vector2f* getPosPtr() { return &pos; }

	const Vector2f& getOrigin() const { return origin; }

	const Vector2f& getScale() const { return scale; }

	const Frame& getCurrentFrame() const { return currentFrame; }

	const float& getDepth() const { return depth; }

	const float& getAngle() const { return angle;  }

	const float& getPrevAngle() const { return prevAngle; }

	const float& getZoomModifier() const { return zoomModifier; }

	bool isClickable() { return clickable; }
	bool isInteractsWithCursor() { return interactsWithCursor; }
	bool isClicked() { return clicked; }

	void setIsClicked(bool p_bool) { clicked = p_bool; }

	const Vector2f& getHalfBounds() const { return halfBounds; }

	void setPos(Vector2f p_pos);
	void setScale(Vector2f p_scale);
	void setAngle(float p_angle) { angle = p_angle; }
	void setColor(Color p_color) { color = p_color; }

	void clamp();

	// Move the sprite by an offset
	void move(Vector2f p_v);

	// LoadFrames is mostly useless, and somewhat obsolete. However,
	// keep it anyways or else some refactoring is in order
	void loadFrames(Vector2i p_size);

	// Set the previous pos and angle to be the current pos and angle
	void updatePrev();

	// Virtual update method, if subclasses wish to define their own
	// update method
	virtual void update(const float& p_dt);

	// Virtial method to play an AnimationCycle
	virtual void play(AnimationCycle& p_cycle);

	virtual void onCollisionBegin(Sprite* p_sprite);
	virtual void duringCollision(Sprite* p_sprite);
	virtual void onCollisionEnd(Sprite* p_sprite);

protected:
	std::string name;

	SDL_Texture* tex;
	Color color;

	// These 2 are useless. I think this is dead code
	SDL_Rect src;
	SDL_Rect dst;

	// Fairly self explanitory here
	Uint8 alpha;
	SDL_RendererFlip flip;

	// Prev pos is the keep a record of where the sprite was in
	// the last time step, so that the renderer can "guess" where the 
	// sprite should be drawn in between timesteps
	Vector2f prevPos;
	Vector2f pos;

	// Straight forward here
	Vector2f origin;
	Vector2i frameSize;
	Vector2f scale;
	float angle;
	float prevAngle;
	float depth;

	// Set to 0 if you wish for this sprite to be an exeption
	// from the camera's zoom
	float zoomModifier;

	// Every sprite has the potential to be a clickable
	bool clickable;
	bool interactsWithCursor;
	bool clicked;
	Vector2f halfBounds;

	// Should the sprite be deleted?
	bool pleaseDelete = false;

	// The current section of the texture to be rendered
	Frame currentFrame;

	// This here is deprecated, but don't delete it unless you
	// want to do some refactoring
	std::vector<Frame> frames;

};