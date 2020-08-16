#include "Text.hpp"

Text::Text()
{

}
Text::Text(const SpriteCreateInfo& p_info, const char* p_string, TTF_Font* p_font, SDL_Color* p_color)
:Sprite(p_info)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(p_font, p_string, p_olor);
	tex = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	frameSize = Vector2i(surfaceMessage->w, surfaceMessage->h);
}

void Text::setText(const char* p_string, TTF_Font* p_font, SDL_Color p_color)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(p_font, p_string, p_olor);
	tex = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	frameSize = Vector2i(surfaceMessage->w, surfaceMessage->h);
}



void Text::update(const float& p_dt)
{
	
}

