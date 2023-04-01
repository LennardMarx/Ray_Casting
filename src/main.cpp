#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <unistd.h>

#include "../include/UI.h"
#include "../include/lightSource.h"
#include "../include/rectangle.h"

int main()
{
    chdir(SDL_GetBasePath());
    srand((unsigned int)time(NULL));

    UI ui{ 1200, 800 };

    const int FPS = 100;                // set FPS
    const int frameDelay = 1000 / FPS; // delay according to FPS
    Uint32 frameStart;                 // keeps track of time (?)
    int frameTime;

    std::vector<std::array<float, 4>> walls;
    // add screen borders
    walls.push_back({ -ui.sizeX / 2 - 1, -ui.sizeY / 2 - 1, -ui.sizeX / 2 - 1, ui.sizeY / 2 + 1 });
    walls.push_back({ -ui.sizeX / 2 - 1, -ui.sizeY / 2 - 1, ui.sizeX / 2 + 1, -ui.sizeY / 2 - 1 });
    walls.push_back({ -ui.sizeX / 2 - 1, ui.sizeY / 2 + 1, ui.sizeX / 2 + 1, ui.sizeY / 2 + 1 });
    walls.push_back({ ui.sizeX / 2 + 1, -ui.sizeY / 2 - 1, ui.sizeX / 2 + 1, ui.sizeY / 2 + 1 });

    Rectangle rectangle1(-400, -200, 200, 200);
    Rectangle rectangle2(0, 50, 250, 250);
    Rectangle rectangle3(150, -300, 150, 150);
    Rectangle rectangle4(-500, 200, 100, 100);

    // following append not working!!
    //walls.insert(walls.end(), rectangle.getWalls().begin(), rectangle.getWalls().end()); // append walls vectors
    for (int i = 0; i < 4; i++)
    {
        walls.push_back(rectangle1.getWalls().at(i));
        walls.push_back(rectangle2.getWalls().at(i));
        walls.push_back(rectangle3.getWalls().at(i));
        walls.push_back(rectangle4.getWalls().at(i));
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

            rectangle1.draw(ui);
            rectangle2.draw(ui);
            rectangle3.draw(ui);
            rectangle4.draw(ui);

            // SDL_PumpEvents();
            mouseState = SDL_GetMouseState(&x, &y);
            lightSource.setPosition(ui, x, y);
            lightSource.emitLight(ui, walls);

            ui.present(); // render screen
        }     // end else (pause game)

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