#pragma once

#include <SDL2/SDL.h>
#include "Math.hpp"
#include "Camera.hpp"

// Nice little package for LMB, RMB, MMB, and mouse pos
class Controls
{
public:
	Controls()
	:
	camera(nullptr),
	leftClick(false), 
	rightClick(false),
	middleClick(false),
	mouseWheelDelta(0)
		
	{}

	void setCamera(const Camera* p_camera) { camera = p_camera; }

	const Vector2f* getWorldMousePos() const;
	const Vector2f* getScreenMousePos() const;
	bool isLeftClick();
	bool isRightClick();
	bool isMiddleClick();

	void update(SDL_Event* p_event);
	void printState();

private:
	// Ptr to camera needed to gather the in-world mouse coords
	const Camera* camera;

	bool leftClick;
	bool rightClick;
	bool middleClick;

	// Amount of scrolling done in a set amout of time
	int mouseWheelDelta;

	Vector2f worldMousePos;
	Vector2f screenMousePos;
};