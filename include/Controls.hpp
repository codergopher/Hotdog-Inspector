#pragma once

#include <SDL2/SDL.h>

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