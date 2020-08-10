#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>

#include <json/json.h>
#include <fstream>


#include "Game.hpp"

#include "Math.hpp"
#include "RenderWindow.hpp"

#include "Controls.hpp"

bool kBox2DScale = 30.f;

bool gShowFrameRate = false;

int gWinWidth = 1280;
int gWinHeight = 720;

Vector2f gGravity = {0.f, 0.f};

bool gKeys[4] = {false, false, false, false};
bool gMouse[5] = {false, false, false, false, false};
int gMouseWheelDelta = 0;

float* gCameraZoom = nullptr;

// Get the amount of time in milliseconds that the 
// program has been running for
double hireTimeInSeconds()
{
	double t = SDL_GetTicks();
	t *= 0.001f;
	return t;
}


int main(int argc, char* args[])
{	
	// Seed the random funtion, so that
	// we can get truly random numbers
	srand((unsigned)time(0));


	// Initialise SDL and SDL_image
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "Failed to init SDL. ERROR : " << SDL_GetError() << std::endl;
	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "Failed to init SDL_image ERROR :" << IMG_GetError() << std::endl;
	
	// Window/renderer combo. 
	RenderWindow window("HotDog Inspector v1.0 FPS:", gWinWidth, gWinHeight);

	// The game icon(see the taskbar when you run the game)
	SDL_Surface* icon = window.loadSurface("res/idea_1.png");
	window.setIcon(icon);

	// The game
	Game game(&window);
	

	// Time stepping

	// Dt is deltaTime. This is the amount of times we update our game per second
	const double dt = 0.01f; // 100 updates per second

	// The accumulater allows us to have smooth rendering.
	// Since our game runs at a set amout of updates per seconds,
	// we want to be able to render between updates
	double accumulator = 0.0f;
	double currentTime = hireTimeInSeconds();

	double oneSecond = 0;
	int framesRenderedInOneSecond = 0;

	while(!game.shouldQuit())
	{
		double newTime = hireTimeInSeconds();
		double frameTime = newTime - currentTime;

		// Avoid the spiral of death. If the program is too slow, don't update the game

		if (frameTime > 0.25f)
			frameTime = 0.f;

		currentTime = newTime;

		accumulator += frameTime;
		oneSecond += frameTime;

		// If enough time has passed to do a game step, then update the game
		while (accumulator >= dt)
		{



			game.mainLoop(dt);


			accumulator -= dt;
		}

		// Print the frame rate if we wish to
		if (gShowFrameRate && oneSecond >= 1)
		{
			std::cout << "FPS: " << framesRenderedInOneSecond << std::endl;

			oneSecond = 0;
			framesRenderedInOneSecond = 0;
		}

		// Alpha is the value we need to determine the position of sprites
		// between time steps
		const double alpha = accumulator / dt;

		// Clear the screen
		window.clear();

		// Render the game
		window.render(game.getWorld(), alpha);

		// Draw what we have rendered to the screen
		window.display();


		// Now 1 frame has passed, so we increment the amount of frames rendered in 1 second
		framesRenderedInOneSecond++;
	}

	window.cleanup();
	

	// Clean up SDL	
	SDL_Quit();
	IMG_Quit();
	return 0;
}

