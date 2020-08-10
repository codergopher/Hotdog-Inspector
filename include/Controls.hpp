#pragma once

#include <SDL2/SDL.h>
#include <Math.hpp>

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
	:mouseWheelDelta(4)
	{}
	Vector2f getWorldMousePos();
	Vector2f getScreenMousePos();
	bool isLeftClick();
	bool isRightClick();
	bool isMiddleClick();

	void update(SDL_Event* p_event);
	void printState();

private:
	bool leftClick;
	bool rightClick;
	bool middleClick;

	int mouseWheelDelta;
};