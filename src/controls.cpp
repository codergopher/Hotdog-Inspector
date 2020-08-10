#include <SDL2/SDL.h>

#include "Math.hpp"
#include "Controls.hpp"
#include "Camera.hpp"

extern int gMouseWheelDelta;


const Vector2f* Controls::getWorldMousePos() const
{

	return &worldMousePos;
}

const Vector2f* Controls::getScreenMousePos() const
{
	return &screenMousePos;
}

bool Controls::isLeftClick()
{
	return leftClick;
}

bool Controls::isRightClick()
{
	return rightClick;
}

bool Controls::isMiddleClick()
{
	return middleClick;
}


void Controls::update(SDL_Event* p_event)
{
	//update the world mouse position

	Vector2i mouseCoords;

	SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
	worldMousePos = toVector2f(mouseCoords);


	worldMousePos -= camera->getPos() + camera->getHalfSize();
	worldMousePos /= camera->getZoom();

	//update the screen mouse position

	mouseCoords = {0, 0};

	SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);

	screenMousePos = toVector2f(mouseCoords);

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
				rightClick = false;
				break;
			case SDL_BUTTON_MIDDLE:
				middleClick = false;
				break;
		}	
	}
	else if (p_event->type == SDL_MOUSEWHEEL)
	{
		if (p_event->wheel.y != 0)
			mouseWheelDelta += p_event->wheel.y;

		else
			mouseWheelDelta = 0;
	}


}

void Controls::printState()
{
	std::cout << "Mouse screen coords: ";
	screenMousePos.print();
	std::cout << std::endl;
	std::cout << "Mouse world coords: ";
	worldMousePos.print();

	std::cout << "Left Mouse Button: " << leftClick << std::endl;
	std::cout << "Right Mouse Mutton: " << rightClick << std::endl;
	std::cout << "Middle Mouse Button: " << middleClick << std::endl;
	std::cout << "Mouse wheel delta: " << mouseWheelDelta << std::endl; 
}