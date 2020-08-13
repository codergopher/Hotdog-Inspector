#include "ClickableSpawner.hpp"
#include "Game.hpp"

extern int gWinWidth;
extern int gWinHeight;

Game::Game(RenderWindow* p_window)
:
window(p_window),
world(&controls)
{
	//disable the nasty looking cursor to make way for ours
	SDL_ShowCursor(SDL_DISABLE);

	loadTextures();
	loadWorld();

}

Game::~Game()
{

	// Destroys all textures that haven't been destroyed when we quit the game
	for (std::map<std::string, SDL_Texture*>::iterator i = textures.begin(); i != textures.end(); ++i)
	{
		SDL_DestroyTexture(i->second);
		std::cout << "Destroyed texture " << i->first << std::endl;
	}
}

std::map<std::string, SDL_Texture*>& Game::getTextures()
{
    return textures;
}

void Game::loadTextures()
{
	// Load our textures, and give each one a name

	SDL_Texture* t0 = window->loadTexture("res/floor_0.png");
	textures.insert(std::pair<std::string, SDL_Texture*>("Floor 0", t0));

	SDL_Texture* t1 = window->loadTexture("res/cursor_0.png");
	textures.insert(std::pair<std::string, SDL_Texture*>("Cursor 0", t1));

	SDL_Texture* t2 = window->loadTexture("res/conveyor_belt_0.png");
	textures.insert(std::pair<std::string, SDL_Texture*>("Conveyor 0", t2));

	SDL_Texture* t3 = window->loadTexture("res/frame_0.png");
	textures.insert(std::pair<std::string, SDL_Texture*>("Frame 0", t3));

	SDL_Texture* t4 = window->loadTexture("res/font.png");
	textures.insert(std::pair<std::string, SDL_Texture*>("Font 0", t4));

	SDL_Texture* t5 = window->loadTexture("res/clickable/normal.png");
    textures.insert(std::pair<std::string, SDL_Texture*>("Hotdog 0", t5));

}

void Game::loadWorld()
{	

	// create the world

	// The camera. First param is the position of cam, second is the view port of the camera
	world.createCamera(Vector2f(0, 0), Vector2f(gWinWidth, gWinHeight));

	// The controls need a ptr to the camera, so that we can calculate the
	// in game coordinates of the mouse
	controls.setCamera(&world.getCamera());
	
	// The floor
	{
		SpriteCreateInfo createInfo = {};
		createInfo.name = "Floor";
		createInfo.tex = textures["Floor 0"];
		createInfo.alpha = 255;
		createInfo.flip = SDL_FLIP_NONE;
		createInfo.pos = Vector2f(0, 0);
		createInfo.origin = Vector2f(31.5, 31.5);
		createInfo.frameSize = Vector2i(64, 64);
		createInfo.scale = Vector2f(1.0f, 1.0f);
		createInfo.depth = 0;
		createInfo.zoomModifier = 1.f;

		createInfo.clickable = true;
		createInfo.halfBounds = Vector2f(32.f, 32.f);
		world.createSprite(createInfo, 0);	
	
	}

	//cursor
	{
		SpriteCreateInfo createInfo = {};
		createInfo.name = "Cursor";
		createInfo.tex = textures["Cursor 0"];
		createInfo.alpha = 255;
		createInfo.flip = SDL_FLIP_NONE;
		createInfo.pos = Vector2f(0, 0);
		createInfo.origin = Vector2f(2.5f, 2.5f);
		createInfo.frameSize = Vector2i(5, 5);
		createInfo.scale = Vector2f(1.0f, 1.0f);
		createInfo.depth = 0;
		createInfo.zoomModifier = 1.f;

		// It's a clickable!
		createInfo.clickable = true;
		createInfo.halfBounds = Vector2f(2.5f, 2.5f);

		Cursor* c = world.createCursor(createInfo, 8);
		c->init();
		c->setControls(&controls);
	}

	// The Conveyor
	{
		SpriteCreateInfo createInfo = {};
		createInfo.name = "Conveyor";
		createInfo.tex = textures["Conveyor 0"];
		createInfo.alpha = 255;
		createInfo.flip = SDL_FLIP_NONE;
		createInfo.pos = Vector2f(0, -4);
		createInfo.angle = 0.0f;
		createInfo.origin = Vector2f(31, 16);
		createInfo.frameSize = Vector2i(62, 38);
		createInfo.scale = Vector2f(1.0f, 1.0f);
		createInfo.depth = 0;
		createInfo.zoomModifier = 1.f;

		// it's a clickable
		createInfo.clickable = true;
		createInfo.halfBounds = Vector2f(31.f, 16.f);

	    world.createConveyor(createInfo, 0);
	}

	// text test
	{
		SpriteCreateInfo createInfo = {};
		createInfo.name = "Text";
		createInfo.tex = textures["Font 0"];
		createInfo.alpha = 255;
		createInfo.color = Color(255, 255, 255);
		createInfo.flip = SDL_FLIP_NONE;
		createInfo.pos = Vector2f(-48, 0);
		createInfo.origin = Vector2f(0, 0);
		createInfo.frameSize = Vector2i(4, 5);
		createInfo.scale = Vector2f(1.0f, 1.0f);
		createInfo.depth = 0;
		createInfo.zoomModifier = 1.f;
		world.createText(createInfo, "cpp is better than python", 8);	
		//world.createCharacter(createInfo, "e", 8);
	}

	// Frame to clip off anything outside the 64x64 playpen
	{
		SpriteCreateInfo createInfo = {};
		createInfo.name = "Frame";
		createInfo.tex = textures["Frame 0"];
		createInfo.alpha = 255;
		createInfo.color = Color(0, 0, 0);
		createInfo.flip = SDL_FLIP_NONE;
		createInfo.pos = Vector2f(0, 0);
		createInfo.origin = Vector2f(114, 64);
		createInfo.frameSize = Vector2i(228, 128);
		createInfo.scale = Vector2f(1.0f, 1.0f);
		createInfo.depth = 0;
		createInfo.zoomModifier = 1.f;
		world.createSprite(createInfo, 10);	
	}

	ClickableSpawner clickableSpawner(&world, textures);
}

// Should the game quit?
bool Game::shouldQuit()
{
	return quit;
}

// Main loop for the game
void Game::mainLoop(const float& p_dt)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			quit = true;
		else
		{
			// Update the state of the controls
			controls.update(&event);
		}

	}
	
	// Update the game based on the deltaTime(p_dt)
	world.update(p_dt);
}