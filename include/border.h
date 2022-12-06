#pragma once

#ifndef BORDER_H
#define BORDER_H

#include <array>

class Border
{
public:
    Border();
    ~Border();

    void setRandCoords(UI &ui);

    std::array<int, 4> getCoords();

    void drawBorder(UI &ui);

private:
    int x1, x2, y1, y2;
    std::array<int, 4> coords;
};

#endif