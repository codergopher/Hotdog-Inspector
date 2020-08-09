#include <SDL2/SDL.h>

#include "Math.hpp"
#include "Controls.hpp"

extern int gMouseWheelDelta;


Vector2f Controls::getWorldMousePos()
{
	return Vector2f(0, 0);
}

Vector2f Controls::getScreenMousePos()
{
	Vector2i mouseCoords;

	SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);

	return toVector2f(mouseCoords);
}

bool Controls::isLeftClick()
{
	return false;
}

bool Controls::isRightClick()
{
	return false;
}

void Controls::update(SDL_Event* p_event)
{
	mouseWheelDelta = 0;

	if (p_event->type == SDL_MOUSEBUTTONDOWN)
	{
		switch (p_event->button.button)
		{
			case SDL_BUTTON_LEFT:
				leftClick = true;
				break;
			case SDL_BUTTON_RIGHT:
				rightClick = true;
				break;
			case SDL_BUTTON_MIDDLE:
				middleClick = true;
				break;
		}
	}
	else if (p_event->type == SDL_MOUSEBUTTONUP)
	{
		switch (p_event->button.button)
		{
			case SDL_BUTTON_LEFT:
				leftClick = false;
				break;
			case SDL_BUTTON_RIGHT:
				leftClick = false;
				break;
			case SDL_BUTTON_MIDDLE:
				leftClick = false;
				break;
		}	
	}
	else if (p_event->type == SDL_MOUSEWHEEL)
	{
		if (p_event->wheel.y != 0)
			mouseWheelDelta += event->wheel.y;
	}

	else
		return;
}
