#include <SDL2/SDL.h>
#include <array>
#include "../include/UI.h"
#include "../include/rectangle.h"


Rectangle::Rectangle(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h)
{
    // defineWalls();
    storeWalls();
}
Rectangle::~Rectangle() {}

void Rectangle::setPos(int _x, int _y)
{
    x = _x;
    y = _y;
}
std::array<int, 2> Rectangle::getPos()
{
    pos.at(0) = x;
    pos.at(1) = y;
    return pos;
}

void Rectangle::setSize(int _w, int _h)
{
    w = _w;
    h = _h;
}
std::array<int, 2> Rectangle::getSize()
{
    size.at(0) = w;
    size.at(1) = h;
    return size;
}

void Rectangle::draw(UI &ui)
{
    ui.drawLine(x, y, x, y+h);
    ui.drawLine(x, y, x+w, y);
    ui.drawLine(x+w, y+h, x+w, y);
    ui.drawLine(x+w, y+h, x, y+h);

    // ui.drawLine(x-w/2, y-h/2, x-w/2, y+h/2);
    // ui.drawLine(x-w/2, y-h/2, x+w/2, y-h/2);
    // ui.drawLine(x+w/2, y+h/2, x+w/2, y-h/2);
    // ui.drawLine(x+w/2, y+h/2, x-w/2, y+h/2);
}

void Rectangle::storeWalls()
{
    walls.push_back({x, y, x, y+h});
    walls.push_back({x, y, x+w, y});
    walls.push_back({x+w, y, x+w, y+h});
    walls.push_back({x, y+h, x+w, y+h});
}

std::vector<std::array<int, 4>> Rectangle::getWalls()
{
    return walls;
}

