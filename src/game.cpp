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

	SDL_Texture* t1 = window->loadTexture("res/test_0.png");
	textures.insert(std::pair<std::string, SDL_Texture*>("box", t1));

	SDL_Texture* t2 = window->loadTexture("res/conveyor_belt_0.png");
	textures.insert(std::pair<std::string, SDL_Texture*>("Conveyor Belt 0", t2));

	SDL_Texture* t3 = window->loadTexture("res/frame_0.png");
	textures.insert(std::pair<std::string, SDL_Texture*>("Frame 0", t3));


}

void Game::loadWorld()
{
	world.createCamera(Vector2f(0, 0), Vector2f(gWinWidth, gWinHeight));

	//test
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

	//box
	{
		SpriteCreateInfo createInfo = {};
		createInfo.name = "Box";
		createInfo.tex = textures["box"];
		createInfo.alpha = 255;
		createInfo.flip = SDL_FLIP_NONE;
		createInfo.pos = Vector2f(10, -23);
		createInfo.origin = Vector2f(4, 4);
		createInfo.frameSize = Vector2i(8, 8);
		createInfo.scale = Vector2f(1.0f, 1.0f);
		createInfo.depth = 0;
		createInfo.zoomModifier = 1.f;
		world.createSprite(createInfo, 0);	
	
	}

	{
		SpriteCreateInfo createInfo = {};
		createInfo.name = "Conveyor";
		createInfo.tex = textures["Conveyor Belt 0"];
		createInfo.alpha = 255;
		createInfo.flip = SDL_FLIP_NONE;
		createInfo.pos = Vector2f(0, 0);
		createInfo.angle = 0.0f;
		createInfo.origin = Vector2f(32, 32);
		createInfo.frameSize = Vector2i(64, 64);
		createInfo.scale = Vector2f(1.0f, 1.0f);
		createInfo.depth = 0;
		createInfo.zoomModifier = 1.f;
		world.createConveyor(createInfo, 0);	
	
	}

	{
		SpriteCreateInfo createInfo = {};
		createInfo.name = "Frame";
		createInfo.tex = textures["Frame 0"];
		createInfo.alpha = 255;
		createInfo.color = Color(0, 0, 0);
		createInfo.flip = SDL_FLIP_NONE;
		createInfo.pos = Vector2f(0, 0);
		createInfo.origin = Vector2f(64, 64);
		createInfo.frameSize = Vector2i(128, 128);
		createInfo.scale = Vector2f(1.0f, 1.0f);
		createInfo.depth = 0;
		createInfo.zoomModifier = 1.f;
		world.createSprite(createInfo, 7);	
	}
}


bool Game::shouldQuit()
{
	return quit;
}

void Game::mainLoop(const float& p_dt)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			quit = true;
		else
		{

		}
	}

	world.update(p_dt);

	world.refresh();
}