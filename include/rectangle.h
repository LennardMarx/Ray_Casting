#pragma once

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <array>
#include <vector>

class Rectangle
{
public:
    Rectangle(int, int, int, int);
    ~Rectangle();

    void setPos(int, int);
    std::array<int, 2> getPos();

    void setSize(int, int);
    std::array<int, 2> getSize();

    void draw(UI &ui);

    void storeWalls();
    std::vector<std::array<int, 4>> getWalls();

private:
    int x, y, w, h;
    std::array<int, 2> pos;
    std::array<int, 2> size;
    std::vector<std::array<int, 4>> walls;
};

#endif