#include <SDL2/SDL.h>
#include <array>
#include "../include/UI.h"
#include "../include/border.h"


Border::Border() {}
Border::~Border() {}
void Border::setRandCoords(UI &ui)
{
    x1 = (rand() % ((ui.sizeX)) - ((ui.sizeX / 2)));
    x2 = (rand() % ((ui.sizeX)) - ((ui.sizeX / 2)));
    y1 = (rand() % ((ui.sizeY)) - ((ui.sizeY / 2)));
    y2 = (rand() % ((ui.sizeY)) - ((ui.sizeY / 2)));
}
std::array<int, 4> Border::getCoords()
{
    coords.at(0) = x1;
    coords.at(1) = y1;
    coords.at(2) = x2;
    coords.at(3) = y2;
    return coords;
}
void Border::drawBorder(UI &ui)
{
    // setRandCoords(ui);
    ui.drawLine(x1, y1, x2, y2);
}