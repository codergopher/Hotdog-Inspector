#include "Game.hpp"

extern int gWinWidth;
extern int gWinHeight;

Game::Game(RenderWindow* p_window)
:
window(p_window)
{
	loadTextures();
	loadWorld();
	
}

Game::~Game()
{
	for (std::map<std::string, SDL_Texture*>::iterator i = textures.begin(); i != textures.end(); ++i)
	{
		SDL_DestroyTexture(i->second);
		std::cout << "Destroyed texture " << i->first << std::endl;
	}
}
void Game::loadTextures()
{
	SDL_Texture* t0 = window->loadTexture("res/idea_1.png");
	textures.insert(std::pair<std::string, SDL_Texture*>("t0", t0));

}

void Game::loadWorld()
{
	world.createCamera(Vector2f(0, 0), Vector2f(gWinWidth, gWinHeight));

	// skye gradient
	{
		SpriteCreateInfo createInfo = {};
		createInfo.name = "t0";
		createInfo.tex = textures["t0"];
		createInfo.alpha = 255;
		createInfo.flip = SDL_FLIP_NONE;
		createInfo.pos = Vector2f(0, 0);
		createInfo.origin = Vector2f(32, 32);
		createInfo.frameSize = Vector2i(64, 64);
		createInfo.scale = Vector2f(1.0f, 1.0f);
		createInfo.depth = 0;
		createInfo.zoomModifier = 1.f;
		world.createSprite(createInfo, 0);	
	
	}

}


void Game::mainLoop(const float& p_dt)
{
	world.update(p_dt);

	world.refresh();
}