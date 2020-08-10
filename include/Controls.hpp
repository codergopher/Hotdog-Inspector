#pragma once

#include <SDL2/SDL.h>
#include "Math.hpp"
#include "Camera.hpp"


enum KEY_DEFS
{
	W,
	A,
	S,
	D,
};

enum MOUSE_DEFS
{
	LCLICK = 1,
	RCLICK = 2,
	MCLICK = 3,
};

void getKeyBoardState(SDL_Event& event, bool* keys);

void getMouseState(SDL_Event& event, bool* mouse);

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
	const Camera* camera;

	bool leftClick;
	bool rightClick;
	bool middleClick;

	int mouseWheelDelta;

	Vector2f worldMousePos;
	Vector2f screenMousePos;
};