

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"
#include "GameWorld.hpp"
#include "Camera.hpp"

// Window/renderer combo
class RenderWindow
{
public:
	// Constructor. Takes a title, and size of window
	RenderWindow(){}
	RenderWindow(const char* p_title, int p_w, int p_h);

	// Load a SDL_Texture
	SDL_Texture* loadTexture(const char* p_fileName);

	// Load a SDL_Surface. SDL2 uses SDL_Surfaces for limited applications
	// Mostly use SDL_Textures
	SDL_Surface* loadSurface(const char* p_fileName);

	// Set the icon of the window
	void setIcon(SDL_Surface* p_icon);

	// Change the title if you wish
	void setTitle(std::string p_title);

	// Clear the screen
	void clear();

	// Render the game world
	void render(GameWorld& p_world, const double& p_alpha);
	
	// Display the render to the screen
	void display();

	// Clean up anything that might need cleaning up before SDL quits
	void cleanup();
private:
	// The window
	SDL_Window* window;
	// The renderer. GPU accelerated
	SDL_Renderer* renderer;
	// A list of all textures loaded
	std::vector<SDL_Texture*> textures;
	// A list of all surfaces loaded
	std::vector<SDL_Surface*> surfaces;
};