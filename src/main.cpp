#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <unistd.h>

#include "../include/UI.h"
#include "../include/border.h"
#include "../include/lightSource.h"
#include "../include/rectangle.h"

int main()
{
        chdir(SDL_GetBasePath());
    srand((unsigned int)time(NULL));

    UI ui{1200, 800};

    const int FPS = 50;                // set FPS
    const int frameDelay = 1000 / FPS; // delay according to FPS
    Uint32 frameStart;                 // keeps track of time (?)
    int frameTime;

    std::vector<Border *> borders;
    for (int i = 0; i < 1; ++i)
    {
        borders.push_back(new Border);
        borders.at(i)->setRandCoords(ui);
    }

    std::vector<std::array<int, 4>> walls;

    Rectangle rectangle(-100, -100, 200, 200);
    // following append not working!!
    //walls.insert(walls.end(), rectangle.getWalls().begin(), rectangle.getWalls().end()); // append walls vectors
    for (int i = 0; i < rectangle.getWalls().size(); i++)
    {
        walls.push_back(rectangle.getWalls().at(i));
    }


    LightSource lightSource;
    Uint32 mouseState;
    int x, y;

    bool pause = false;
    bool quit = false;
    
    SDL_Event event;

    while (!quit)
    {
        frameStart = SDL_GetTicks(); // limit framerate (see end of while loop)

        // pause the game
        if (pause)
        {
            // do nothing
        }
        else
        {
            ui.clear(); // render screen black

            rectangle.draw(ui);

            SDL_PumpEvents();
            mouseState = SDL_GetMouseState(&x, &y);
            lightSource.setPosition(ui, x, y);
            lightSource.emitLight(ui, walls);

            ui.present(); // render screen
        }                 // end else (pause game)

        while (SDL_PollEvent(&event))
        {
            // stop when pressing "x" (?)
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            // key presses
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_SPACE:
                    pause = !pause;
                    break;
                default:
                    break;
                }
            }
        }
        // frame time to limit FPS
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    return 0;
}