#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Sprite.hpp"
#include "Camera.hpp"
#include "Math.hpp"

extern SDL_Renderer* gRenderer;

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
		std::cout << "Failed to create SDL_Window. ERROR: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	gRenderer = renderer;
	if (renderer == NULL)
		std::cout << "Failed to create SDL_Renderer. ERROR: " << SDL_GetError() << std::endl; 
}

SDL_Texture* RenderWindow::loadTexture(const char* p_fileName)
{

	    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( p_fileName);
    if( loadedSurface == NULL )
    {
        std::cout << "Unable to load image " << p_fileName << std::endl;
        std::cout << "SDL_image Error: " << std::endl;
        std::cout << IMG_GetError() << std::endl;
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
	        std::cout << "Unable to create texture from " << p_fileName << std::endl;
	        std::cout << "SDL_image Error: " << std::endl;
	        std::cout << IMG_GetError() << std::endl;
        }


        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    textures.push_back(newTexture);
    return newTexture;
}

SDL_Surface* RenderWindow::loadSurface(const char* p_fileName)
{

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( p_fileName);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", p_fileName, IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        //Create texture from surface pixels
        
    }
    surfaces.push_back(loadedSurface);
    return loadedSurface;
}

void RenderWindow::setIcon(SDL_Surface* p_icon)
{
	SDL_SetWindowIcon(window, p_icon);
}

void RenderWindow::setTitle(std::string p_title)
{
	SDL_SetWindowTitle(window, p_title.c_str());
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(GameWorld& p_world, const double& p_alpha)
{
	std::multimap<int, Sprite*> allSprites = p_world.getAllSprites();

	Camera cam = p_world.getCamera();
	Vector2f camPos = cam.getPos() * p_alpha + cam.getPrevPos() * (1.0f - p_alpha);
	
	for (std::multimap<int, Sprite*>::iterator i = allSprites.begin(); i != allSprites.end(); ++i)
	{
		Sprite* e = i->second;

		float camZoom = cam.getZoom();
		camZoom = camZoom * e->getZoomModifier();

		if(camZoom == 0)
			camZoom = 1;

		Vector2f pos = e->getPos() * p_alpha + e->getPrevPos() * (1.0f - p_alpha);
		Vector2f origin = e->getOrigin();

		float angle = e->getAngle() * p_alpha + e->getPrevAngle() * (1.0f - p_alpha);

		SDL_Point center;

		Vector2f scale = e->getScale();

		center.x = origin.x * scale.x * camZoom;
		center.y = origin.y * scale.y * camZoom;

		Frame frame = e->getCurrentFrame();

		SDL_Texture* tex = e->getTex();
		Color color = e->getColor();



		SDL_RendererFlip flip = e->getFlip();


		
		SDL_Rect src;
		SDL_Rect dst;

		src.x = frame.rect.x;
		src.y = frame.rect.y;
		src.w = frame.rect.w;
		src.h = frame.rect.h;

		double x = (pos.x - origin.x * scale.x) * camZoom - (camPos.x * camZoom * e->getDepth() - cam.getHalfSize().x);
		double y = (pos.y - origin.y * scale.y) * camZoom - (camPos.y * camZoom * e->getDepth() - cam.getHalfSize().y);

		dst.x = roundToInt(roundToScale(x, 1/camZoom));
		dst.y = roundToInt(roundToScale(y, 1/camZoom));
		dst.w = frame.rect.w * scale.x * camZoom;
		dst.h = frame.rect.h * scale.y * camZoom;

		SDL_SetTextureAlphaMod(tex, e->getAlpha());
		SDL_SetTextureColorMod(tex, color.r, color.g, color.b);


		if (SDL_RenderCopyEx(renderer, tex, &src, &dst, angle, &center, flip))
			std::cout << "SDL_RenderCopy failed! " << SDL_GetError() << std::endl;
	}


}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::cleanup()
{
	for (auto& t : textures)
	{
		SDL_DestroyTexture(t);
	}

	for (auto& s : surfaces)
	{
		SDL_FreeSurface(s);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

}