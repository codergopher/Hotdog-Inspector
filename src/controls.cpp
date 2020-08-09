#include <SDL2/SDL.h>

#include "Controls.hpp"

extern int gMouseWheelDelta;

void getKeyBoardState(SDL_Event& event, bool* keys)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_w:
				keys[W] = true;
				break;
			case SDLK_a:
				keys[A] = true;
				break;
			case SDLK_s:
				keys[S] = true;
				break;
			case SDLK_d:
				keys[D] = true;
				break;

		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_w:
				keys[W] = false;
				break;
			case SDLK_a:
				keys[A] = false;
				break;
			case SDLK_s:
				keys[S] = false;
				break;
			case SDLK_d:
				keys[D] = false;
				break;
		}
	}
	else
		return;
}

void getMouseState(SDL_Event& event, bool* mouse)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		switch (event.button.button)
		{
			case SDL_BUTTON_LEFT:
				mouse[LCLICK] = true;
				break;
			case SDL_BUTTON_RIGHT:
				mouse[RCLICK] = true;
				break;
			case SDL_BUTTON_MIDDLE:
				mouse[MCLICK] = true;
				break;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		switch (event.button.button)
		{
			case SDL_BUTTON_LEFT:
				mouse[LCLICK] = false;
				break;
			case SDL_BUTTON_RIGHT:
				mouse[RCLICK] = false;
				break;
			case SDL_BUTTON_MIDDLE:
				mouse[MCLICK] = false;
				break;
		}	
	}
	else if (event.type == SDL_MOUSEWHEEL)
	{
		if (event.wheel.y != 0)
			gMouseWheelDelta += event.wheel.y;
	}

	else
		return;
}
