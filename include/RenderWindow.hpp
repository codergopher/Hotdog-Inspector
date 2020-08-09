#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"
#include "GameWorld.hpp"
#include "Camera.hpp"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_fileName);
	SDL_Surface* loadSurface(const char* p_fileName);

	void setIcon(SDL_Surface* p_icon);

	void setTitle(std::string p_title);
	void clear();
	void render(GameWorld& p_world, const double& p_alpha);
	void display();
	void cleanup();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<SDL_Texture*> textures;
	std::vector<SDL_Surface*> surfaces;
};