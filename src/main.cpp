#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

#include <jsoncpp/json/json.h>
#include <fstream>

#include <Box2D/Box2D.h>

#include "Game.hpp"

#include "Math.hpp"
#include "RenderWindow.hpp"

#include "Controls.hpp"

bool kBox2DScale = 30.f;

bool gShowFrameRate = true;

int gWinWidth = 1280;
int gWinHeight = 720;

Vector2f gGravity = {0.f, 0.f};

bool gKeys[4] = {false, false, false, false};
bool gMouse[5] = {false, false, false, false, false};
int gMouseWheelDelta = 0;

float* gCameraZoom = nullptr;

double hireTimeInSeconds()
{
	double t = SDL_GetTicks();
	t *= 0.001f;
	return t;
}


int main(int argc, char* args[])
{	
	srand((unsigned)time(0));

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "Failed to init SDL. ERROR : " << SDL_GetError() << std::endl;
	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "Failed to init SDL_image ERROR :" << IMG_GetError() << std::endl;
	
	RenderWindow window("HotDog Inspector v1.0 FPS:", gWinWidth, gWinHeight);

	SDL_Surface* icon = window.loadSurface("res/idea_1.png");
	Game game(&window);
	window.setIcon(icon);


	SDL_Event event;

	bool quit = false;

	// Time stepping
	const double dt = 0.01f;
	double accumulator = 0.0f;
	double currentTime = hireTimeInSeconds();

	double oneSecond = 0;
	int framesRenderedInOneSecond = 0;

	while(!quit)
	{
		double newTime = hireTimeInSeconds();
		double frameTime = newTime - currentTime;

		// Avoid the spiral of death

		if (frameTime > 0.25f)
			frameTime = 0.f;

		currentTime = newTime;

		accumulator += frameTime;
		oneSecond += frameTime;

		while (accumulator >= dt)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					quit = true;
				else
				{
					getKeyBoardState(event, gKeys);
					getMouseState(event, gMouse);
				}
			}


			game.mainLoop(dt);


			accumulator -= dt;
		}

		if (gShowFrameRate && oneSecond >= 1)
		{
			std::cout << "FPS: " << framesRenderedInOneSecond << std::endl;

			oneSecond = 0;
			framesRenderedInOneSecond = 0;
		}

		const double alpha = accumulator / dt;

		window.clear();
		window.render(game.getWorld(), alpha);
		window.display();

		gMouseWheelDelta = 0;
		framesRenderedInOneSecond++;
	}

	window.cleanup();
	
	SDL_Quit();
	IMG_Quit();
	return 0;
}

