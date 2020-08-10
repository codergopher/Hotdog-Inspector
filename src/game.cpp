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
		createInfo.origin = Vector2f(32, 32);
		createInfo.frameSize = Vector2i(64, 64);
		createInfo.scale = Vector2f(1.0f, 1.0f);
		createInfo.depth = 0;
		createInfo.zoomModifier = 1.f;
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

		// Info for the clickable
		ClickableCreateInfo clickableInfo = {};
		clickableInfo.pos = Vector2f(0, 0);
		clickableInfo.halfSize = Vector2f(2.5f, 2.5f);

		// Create the clickable
		Clickable* clickable = world.createClickable(clickableInfo);

		// Set the cursor's clickable to be the clickable just created
		createInfo.clickable = clickable;

		Cursor* cursor = world.createCursor(createInfo, 8);

		clickable->setPosPtr(cursor->getPosPtr());



	
	}

	// The Conveyor
	{
		SpriteCreateInfo createInfo = {};
		createInfo.name = "Conveyor";
		createInfo.tex = textures["Conveyor 0"];
		createInfo.alpha = 255;
		createInfo.flip = SDL_FLIP_NONE;
		createInfo.pos = Vector2f(0, 0);
		createInfo.angle = 0.0f;
		createInfo.origin = Vector2f(32, 32);
		createInfo.frameSize = Vector2i(64, 64);
		createInfo.scale = Vector2f(1.0f, 1.0f);
		createInfo.depth = 0;
		createInfo.zoomModifier = 1.f;

		// Info for the clickable
		ClickableCreateInfo clickableInfo = {};
		clickableInfo.pos = Vector2f(0, 0);
		clickableInfo.halfSize = Vector2f(5.f , 5.f);

		// Create the clickable
		Clickable* clickable = world.createClickable(clickableInfo);

		// Set the cursor's clickable to be the clickable just created
		createInfo.clickable = clickable;

		Conveyor* conveyor = world.createConveyor(createInfo, 0);

		clickable->setPosPtr(conveyor->getPosPtr());	
	
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
		createInfo.origin = Vector2f(64, 64);
		createInfo.frameSize = Vector2i(128, 128);
		createInfo.scale = Vector2f(1.0f, 1.0f);
		createInfo.depth = 0;
		createInfo.zoomModifier = 1.f;
		world.createSprite(createInfo, 7);	
	}
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

	// I used to use refresh when I was using Box2D. The refresh method would
	// set the pos of the Sprites to the pos of the Box2D body, if the sprite had a body
	world.refresh();
}