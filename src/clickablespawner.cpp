#include "ClickableSpawner.hpp"

ClickableSpawner::ClickableSpawner(GameWorld* p_gameWorld, std::map<std::string, SDL_Texture*> p_textures)
:world(p_gameWorld), textures(p_textures)

{
    {

        SpriteCreateInfo createInfo = {};
        createInfo.name = "Test";

        createInfo.tex = textures["Hotdog 0"];
        createInfo.alpha = 255;
        createInfo.flip = SDL_FLIP_NONE;
        createInfo.pos = Vector2f(0, 0);
        createInfo.origin = Vector2f(2.5f, 2.5f);
        createInfo.frameSize = Vector2i(5, 5);
        createInfo.scale = Vector2f(1.0f, 1.0f);
        createInfo.depth = 0;
        createInfo.zoomModifier = 1.f;

        //It's a clickable!
        createInfo.clickable = true;
        createInfo.halfBounds = Vector2f(2.5f, 2.5f);

        world->createSprite(createInfo, 9);
    }
}

void ClickableSpawner::update(const float& p_dt)
{

}