#pragma once

#include <map>
#include <string>

#include "Math.hpp"
#include "Game.hpp"
#include "GameWorld.hpp"
#include "Sprite.hpp"

class ClickableSpawner
{
public:
    ClickableSpawner(GameWorld* p_gameWorld, std::map<std::string, SDL_Texture*> p_textures);
    void update(const float& p_dt);
private:

    std::string clickables[1] = {"Hotdog 0"};

    GameWorld* world;
    std::map<std::string, SDL_Texture*> textures;
};