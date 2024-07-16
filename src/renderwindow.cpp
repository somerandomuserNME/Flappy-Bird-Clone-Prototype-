#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h){
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if(window == NULL){
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    }
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filepath){
    SDL_Texture *tex = NULL;
    tex = IMG_LoadTexture(renderer, p_filepath);

    if(tex == NULL){
        std::cout << "Error loading texture. Error " << SDL_GetError() << std::endl;
    }

    return tex;
}

int RenderWindow::getRefreshRate(){
    int displayIndex = SDL_GetWindowDisplayIndex(window);

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}

void RenderWindow::clean(){
    SDL_DestroyWindow(window);
}

void RenderWindow::clear(){
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity){
    SDL_Rect source;
    source.x = entity.getCurrentFrame().x;
    source.y = entity.getCurrentFrame().y;
    source.w = entity.getCurrentFrame().w;
    source.h = entity.getCurrentFrame().h;

    //edit destination to change what is shown on the window    
    SDL_Rect destination;
    destination.x = entity.getPos().x;
    destination.y = entity.getPos().y;
    destination.w = entity.getCurrentFrame().w * 4;
    destination.h = entity.getCurrentFrame().h * 4;

    SDL_RenderCopy(renderer, entity.getTex(), &source, &destination);
}

void RenderWindow::present() {
    SDL_RenderPresent(renderer);
}