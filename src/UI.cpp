#include <SDL2/SDL.h>
#include "../include/UI.h"

UI::UI(int sizeX, int sizeY): sizeX(sizeX), sizeY(sizeY)
{
    initialize(sizeX, sizeY);
}

UI::~UI()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

void UI::clear()
{
    setDrawColor(0, 0, 0, 255);
    SDL_RenderClear(renderer);
    setDrawColor(255, 255, 255, 255);
}

void UI::present()
{
    SDL_RenderPresent(renderer);
}

void UI::drawPixel(int x, int y)
{
    SDL_RenderDrawPoint(renderer, x + sizeX / 2, y + sizeY / 2);
}

void UI::drawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(renderer, x1 + sizeX / 2, y1 + sizeY / 2, x2 + sizeX / 2, y2 + sizeY / 2);
}

void UI::setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

// void UI::setRandCoords()
// {
//     x1 = (rand() % ((sizeX)) - ((sizeX / 2)));
//     x2 = (rand() % ((sizeX)) - ((sizeX / 2)));
//     y1 = (rand() % ((sizeY)) - ((sizeY / 2)));
//     y2 = (rand() % ((sizeY)) - ((sizeY / 2)));
// }
// void UI::drawRandLine()
// {
//     setRandCoords();
//     drawLine(x1, y1, x2, y2);
// }


void UI::initialize(int sizeX, int sizeY)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    // Create a Window
    window = SDL_CreateWindow("Ray Casting", 0, 0, sizeX, sizeY, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // | SDL_RENDERER_PRESENTVSYNC
    // scale window
    // SDL_SetWindowSize(window, sizeX * 3, sizeY * 3);
    // adjust render scale
    // SDL_RenderSetScale(renderer, 3, 3);
    // place window in middle of screen after scaling
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}
