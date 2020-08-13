#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <map>

#include "Controls.hpp"
#include "RenderWindow.hpp"
#include "GameWorld.hpp"
#include "Math.hpp"


// Epic Game class
class Game
{
public:
	Game(RenderWindow* p_window);
	~Game();
	GameWorld& getWorld()
	{
		return world;
	}
	std::map<std::string, SDL_Texture*>& getTextures();
	void loadTextures();
	void loadWorld();
	void mainLoop(const float& p_dt);
	bool shouldQuit();
private:
	// The controls is currently the state of the mouse
	// I am considering placing the controls in the main loop in main.cpp,
	// and then simply using a ptr to the controls here
	Controls controls;

	// SDL_Event lets us know of key presses, and if we close the window
	SDL_Event event;

	// Ptr to the window/render combo, so that we can load our textures
	RenderWindow* window;

	// Where all of the sprites live
	GameWorld world;

	// A list of all the textures we have, by name(hence the std::map)
	std::map<std::string, SDL_Texture*> textures;

	// Should we want to quit the game
	bool quit;
};