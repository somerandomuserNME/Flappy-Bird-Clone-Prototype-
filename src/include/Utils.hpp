#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace utils{
    inline float hireTimeSeconds(){
        float t = SDL_GetTicks();
        t *= 0.001f;

        return t;
    }
}