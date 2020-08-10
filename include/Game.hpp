#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <map>

#include "Controls.hpp"
#include "RenderWindow.hpp"
#include "GameWorld.hpp"
#include "Math.hpp"

class Game
{
public:
	Game(RenderWindow* p_window);
	~Game();
	GameWorld& getWorld()
	{
		return world;
	}
	void loadTextures();
	void loadWorld();
	void mainLoop(const float& p_dt);
	bool shouldQuit();
private:
	Cursor* cursor;
	Controls controls;
	SDL_Event event;
	RenderWindow* window;
	GameWorld world;
	std::map<std::string, SDL_Texture*> textures;
	bool quit;
};