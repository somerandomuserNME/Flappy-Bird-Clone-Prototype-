#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

Entity::Entity(Vector2f position, SDL_Texture* tex)
:pos(position), texture(tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 64; // Scaled by 2
    currentFrame.h = 64; // Scaled by 2
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
    currentFrame.w = 512; // Scaled by 2
    currentFrame.h = 384; // Scaled by 2
}

BirdEntity::BirdEntity(Vector2f position, SDL_Texture* tex)
: Entity(position, tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32; // Scaled by 2
    currentFrame.h = 22; // Scaled by 2
}

PipeEntity::PipeEntity(Vector2f position, SDL_Texture* tex)
: Entity(position, tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 60; // Scaled by 2
    currentFrame.h = 200; // Scaled by 2
}

PipeEntity::PipeEntity()
    : Entity(Vector2f(0, 0), nullptr) { // Initialize with default values
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 60; // Scaled by 2
    currentFrame.h = 200; // Scaled by 2
}
