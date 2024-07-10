#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

class RenderWindow{
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filepath);
    int getRefreshRate();
    void clean();
    void present();
    void clear();
    void render(Entity& entity);
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};