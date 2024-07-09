#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

Entity::Entity(Vector2f position, SDL_Texture* tex)
:pos(position), texture(tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}

SDL_Texture* Entity::getTex(){
    return texture;
}

SDL_Rect Entity::getCurrentFrame(){
    return currentFrame;
}

SkyEntity::SkyEntity(Vector2f position, SDL_Texture* tex)
: Entity(position, tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 256;
    currentFrame.h = 192;
}

BirdEntity::BirdEntity(Vector2f position, SDL_Texture* tex)
: Entity(position, tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 16;
    currentFrame.h = 11;
}

PipeEntity::PipeEntity(Vector2f position, SDL_Texture* tex)
: Entity(position, tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 30;
    currentFrame.h = 100;
}

PipeEntity::PipeEntity()
    : Entity(Vector2f(0, 0), nullptr) { // Initialize with default values
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 30; // Adjust the dimensions as necessary
    currentFrame.h = 100; // Adjust the dimensions as necessary
}