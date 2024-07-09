#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity{
public:
    Entity(Vector2f pos, SDL_Texture* tex);
    // float getX();
    // float getY();
    Vector2f& getPos(){
        return pos;
    }
    SDL_Texture* getTex();
    SDL_Rect getCurrentFrame();
protected:
    Vector2f pos;
    SDL_Rect currentFrame;
    SDL_Texture* texture;
};

class SkyEntity : public Entity{
public:
    SkyEntity(Vector2f position, SDL_Texture* tex);
};

class BirdEntity : public Entity{
public:
    BirdEntity(Vector2f position, SDL_Texture* tex);
};

class PipeEntity : public Entity{
public:
    PipeEntity(Vector2f position, SDL_Texture* tex);
    PipeEntity();  // Default constructor
};