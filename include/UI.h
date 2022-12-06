# pragma once

#ifndef SRC_UI_H_
#define SRC_UI_H_

class UI
{
public:
    const float sizeX;
    const float sizeY;

    UI(int, int);

    ~UI();

    void clear();

    void present();

    void drawPixel(int x, int y);

    void drawLine(int x1, int y1, int x2, int y2);

    void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    // void setRandCoords();

    // void drawRandLine();

private:
    void initialize(int, int);

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    int x1, x2, y1, y2;
};

#endif /* SRC_UI_H_ */