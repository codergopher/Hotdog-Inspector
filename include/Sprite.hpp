#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//#include <Box2D/Box2D.h>

#include <vector>
#include <string>

#include "Math.hpp"
#include "Animation.hpp"

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
};

class Sprite
{
public:

	Sprite(){}
	Sprite(const SpriteCreateInfo& p_info);
	virtual ~Sprite();

	bool shouldDelete() const { return pleaseDelete; }

	const std::string& getName() const { return name; }

	SDL_Texture* getTex() const { return tex; }

	 Color getColor()  { return color; }

	const Uint8& getAlpha() const { return alpha; }

	const SDL_RendererFlip& getFlip() const { return flip; }

	const SDL_Rect& getSrc() const { return src; }

	const SDL_Rect& getDst() const { return dst; }

	const Vector2f& getPrevPos() const {return prevPos; }

	Vector2f& getPos() { return pos; }

	const Vector2f& getOrigin() const { return origin; }

	const Vector2f& getScale() const { return scale; }

	const Frame& getCurrentFrame() const { return currentFrame; }

	const float& getDepth() const { return depth; }

	const float& getAngle() const { return angle;  }

	const float& getPrevAngle() const { return prevAngle; }

	const float& getZoomModifier() const { return zoomModifier; }

	void setPos(Vector2f p_pos);
	void setScale(Vector2f p_scale);
	void setAngle(float p_angle) { angle = p_angle; }
	void setColor(Color p_color) { color = p_color; }


	void loadFrames(Vector2i p_size);
	void updatePrev();
	virtual void update(const float& p_dt);
	virtual void play(AnimationCycle& p_cycle);

protected:
	std::string name;

	SDL_Texture* tex;
	Color color;
	SDL_Rect src;
	SDL_Rect dst;
	Uint8 alpha;
	SDL_RendererFlip flip;
	Vector2f prevPos;
	Vector2f pos;
	Vector2f origin;
	Vector2i frameSize;
	Vector2f scale;
	float angle;
	float prevAngle;
	float depth;
	float zoomModifier;

	bool pleaseDelete = false;

	Frame currentFrame;
	std::vector<Frame> frames;

};