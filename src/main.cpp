#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <random>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

struct PipePair {
    PipeEntity bottomPipe;
    PipeEntity ceilingPipe;
    PipePair(Vector2f position, SDL_Texture* tex1, SDL_Texture* tex2)
        : bottomPipe(position, tex1),
          ceilingPipe(Vector2f(position.x, position.y - 300), tex2) // Scaled by 2
          {}
};

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    return a.x < b.x + b.w &&
           a.x + a.w > b.x &&
           a.y < b.y + b.h &&
           a.y + a.h > b.y;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "IMG_Init has failed. Error " << SDL_GetError() << std::endl;
        return -1;
    }

    RenderWindow window("FlappyBird Clone ~ Prototype", 512, 384); // Scaled by 2
    int windowRefreshRate = window.getRefreshRate();

    SDL_Texture* sky = window.loadTexture("res/sky.png");
    if (!sky) {
        std::cout << "Failed to load sky texture. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Texture* GameOverScreen = window.loadTexture("res/game_over_screen.png");
    if (!GameOverScreen) {
        std::cout << "Failed to load game over screen texture. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Texture* bird = window.loadTexture("res/birdee.png");
    if (!bird) {
        std::cout << "Failed to load bird texture. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Texture* bottomPipeTex = window.loadTexture("res/bottom_pipe.png");
    if (!bottomPipeTex) {
        std::cout << "Failed to load bottom pipe texture. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Texture* topPipeTex = window.loadTexture("res/ceiling_pipe.png");
    if (!topPipeTex) {
        std::cout << "Failed to load top pipe texture. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    std::vector<PipePair> pipes;

    // Setup random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(200, 240); // Scaled by 2

    // Initializing pipes
    for(int i = 0; i < 4; i++){
        int randomY = dis(gen);
        pipes.emplace_back(Vector2f(i * 158 + 512, randomY % 150 + 120), bottomPipeTex, topPipeTex); // Scaled by 2
    }

    // Initializing entities
    SkyEntity cloudySky(Vector2f(0, 0), sky);
    SkyEntity gameOver(Vector2f(0, 0), GameOverScreen);
    BirdEntity birdy(Vector2f(100, 40), bird); // Scaled by 2

    bool running = true;
    SDL_Event windowEvent;

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeSeconds();
    
    float birdSpeed = 120.0f;  // Scaled by 2

    int flag = 1; //This flag will go between 1 and 2, if 1, then the game will run, if 2 it's the gameover screen
    bool collisionFlag = false;

    // Game loop
    while (running) {
        int startTicks = SDL_GetTicks();

        float newTime = utils::hireTimeSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;
        accumulator += frameTime;

        while(accumulator >= timeStep) {
            while(SDL_PollEvent(&windowEvent)) {
                if(windowEvent.type == SDL_QUIT) {
                    running = false;
                }
                if(windowEvent.type == SDL_KEYDOWN && !collisionFlag) {
                    switch (windowEvent.key.keysym.sym) {
                        case SDLK_UP:
                            // std::cout << "Up key was pressed" << std::endl;
                            birdy.getPos().y -= 36; // Scaled by 2
                            break;
                    }
                }
                if(flag == 2 && windowEvent.key.keysym.sym == SDLK_RETURN){
                    // Reset all the game data (ie. bird position, birdSpeed, pipe positioning and setup)
                    birdy.getPos() = Vector2f(100, 40); // Scaled by 2
                    pipes.clear();
                    for(int i = 0; i < 4; i++){
                        int randomY = dis(gen);
                        pipes.emplace_back(Vector2f(i * 158 + 512, randomY % 150 + 120), bottomPipeTex, topPipeTex); // Scaled by 2
                    }
                    birdSpeed = 120.0f; // Scaled by 2
                    collisionFlag = false;
                    flag = 1; // Switch back to the game
                }
            }

            // from the beginning or after the reset, the pipes and the bird information is set/reset and the game progresses as usual
            if(flag == 1){
                // Update bird position
                birdy.getPos().y += birdSpeed * timeStep;

                SDL_Rect birdBoundBox = {static_cast<int>(birdy.getPos().x), 
                                        static_cast<int>(birdy.getPos().y), 
                                        birdy.getCurrentFrame().w, 
                                        birdy.getCurrentFrame().h};

                if(!collisionFlag){
                    // Update pipe positions
                    for (PipePair& p : pipes) {
                        p.bottomPipe.getPos().x -= 200 * timeStep; // Scaled by 2
                        p.ceilingPipe.getPos().x = p.bottomPipe.getPos().x;  // Ensure x position is synchronized

                        SDL_Rect bottomPipeBoundBox = {
                            static_cast<int>(p.bottomPipe.getPos().x),
                            static_cast<int>(p.bottomPipe.getPos().y),
                            p.bottomPipe.getCurrentFrame().w,
                            p.bottomPipe.getCurrentFrame().h
                        };
                        SDL_Rect ceilingPipeBoundBox = {
                            static_cast<int>(p.ceilingPipe.getPos().x),
                            static_cast<int>(p.ceilingPipe.getPos().y),
                            p.ceilingPipe.getCurrentFrame().w,
                            p.ceilingPipe.getCurrentFrame().h
                        };

                        if (!collisionFlag && (checkCollision(birdBoundBox, bottomPipeBoundBox) || checkCollision(birdBoundBox, ceilingPipeBoundBox) || birdy.getPos().y <= 0 || birdy.getPos().y + birdy.getCurrentFrame().h >= 384)) { // Scaled by 2
                            //std::cout << "Collision detected!" << std::endl;
                            collisionFlag = true; //so that the event corresponding to the up-key being pressed is disabled
                            birdSpeed = 800.0f; // Scaled by 2
                        }

                        if (p.bottomPipe.getPos().x < -p.bottomPipe.getCurrentFrame().w) {
                            int randomY = dis(gen);  // Generate a new random Y position
                            p.bottomPipe.getPos().x = 512; // Scaled by 2
                            p.bottomPipe.getPos().y = randomY;
                            p.ceilingPipe.getPos().x = 512; // Scaled by 2
                            p.ceilingPipe.getPos().y = randomY - 300;  // Ensure the pipes are positioned correctly and scaled by 2
                        }
                    }
                }
                if(collisionFlag && birdy.getPos().y + birdy.getCurrentFrame().h >= 384){ // Scaled by 2
                    birdSpeed = 0.0f; // Stop the bird from falling after y-level 384
                    flag = 2; // Set the flag to switch to game over screen
                }
            }
            accumulator -= timeStep;
        }

        const float alpha = accumulator / timeStep;

        window.clear();

        // the if statements determine what gets rendered
        if(flag == 1){
            window.render(cloudySky);

            for (PipePair& p : pipes) {
                window.render(p.ceilingPipe);
                window.render(p.bottomPipe);
            }

            window.render(birdy);
        }
        else if(flag == 2){
            window.render(gameOver);
        }

        window.present();

        int frameTicks = SDL_GetTicks() - startTicks;

        if (frameTicks < 1000 / window.getRefreshRate()) {
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
        }
    }

    window.clean();
    SDL_Quit();

    return EXIT_SUCCESS;
}
