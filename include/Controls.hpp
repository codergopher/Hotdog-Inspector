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
	{}
	Controls(SDL_Event* p_event) 
	:event(p_event)
	{}
	Vector2f getWorldMousePos();
	Vector2f getScreenMousePos();
	bool isLeftClick();
	bool isRightClick();

	void update(SDL_Event* p_event);

private:
	bool leftClick;
	bool rightClick;
	bool middleClick;

	int mouseWheelDelta;

	SDL_Event* event;
};