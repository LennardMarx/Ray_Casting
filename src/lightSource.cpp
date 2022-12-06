#include <SDL2/SDL.h>
#include <cmath>
#include <utility>
#include <vector>

#include "../include/UI.h"
#include "../include/border.h"
#include "../include/lightSource.h"

LightSource::LightSource() {}
LightSource::~LightSource() {}

void LightSource::setPosition(UI &ui, int _x, int _y)
{
    coords.first = _x - ui.sizeX / 2;
    coords.second = _y - ui.sizeY / 2;
}

std::pair<int, int> LightSource::getPosition()
{
    return coords;
}

std::pair<double, double> LightSource::calcIntersection()
{
    intersection.first = x1 + t * (x2 - x1);
    intersection.second = y1 + t * (y2 - y1);
    return intersection;
}
std::pair<float, float> LightSource::getClosestIntersection()
{
    closestIntersection = intersections.at(0);
    for (int i = 0; i < intersections.size(); i++)
    {
        distance = sqrt(pow(intersections.at(i).second - coords.second, 2) + pow(intersections.at(i).first - coords.first, 2));
        if (distance < lastDistance)
        {
            closestIntersection = intersections.at(i);
        }
        lastDistance = distance;
    }
    return closestIntersection;
}

void LightSource::calcIntersections(std::vector<std::array<int, 4>> _walls)
{
    for (int i = 0; i < _walls.size(); i++)
    {
        x3 = x;
        y3 = y;
        x4 = c1;
        y4 = c2;
        x1 = _walls.at(i).at(0);
        y1 = _walls.at(i).at(1);
        x2 = _walls.at(i).at(2);
        y2 = _walls.at(i).at(3);
        denom = ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
        if (denom == 0)
        {
            continue;
        }
        t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
        u = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) / denom;
        if (0 < t && t < 1 && u > 0)
        {
            intersections.push_back(calcIntersection());
        }
    }
}
void LightSource::emitLight(UI &ui, std::vector<std::array<int, 4>> &_walls)
{
    ui.setDrawColor(255, 255, 255, 30);
    for (int i = 0; i < 360; i = i + 2)
    {
        x = coords.first;
        y = coords.second;
        ang = i * pi / 180;
        c1 = x + ui.sizeY * 2 * cos(ang); // coords outside of screen
        c2 = y + ui.sizeY * 2 * sin(ang);
          
        calcIntersections(_walls);
        
        if (!intersections.empty())
        {
            ui.drawLine(x, y, getClosestIntersection().first, getClosestIntersection().second);
        }
        else
        {
            // GET RID OF THAT BY GIVING SCREEN BORDERS!
            ui.drawLine(x, y, c1, c2); // to a place outside of screen
        }
        // clear intersections
        while (!intersections.empty())
        {
           intersections.pop_back();
        }
    }
}