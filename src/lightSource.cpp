#include <SDL2/SDL.h>
#include <cmath>
#include <utility>
#include <vector>
#include <array>

#include "../include/UI.h"
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

std::pair<float, float> LightSource::calcIntersection()
{
    intersection.first = x3 + u * (x4 - x3);
    intersection.second = y3 + u * (y4 - y3);
    return intersection;
}
std::pair<float, float> LightSource::getClosestIntersection()
{
    // closestIntersection = intersections.at(0);
    // lastDistance = sqrt(pow(intersections.at(0).second - coords.second, 2) + pow(intersections.at(0).first - coords.first, 2));
    closestDistance = 1000000;
    for (int i = 0; i < intersections.size(); i++)
    {
        distance = sqrt(pow(intersections.at(i).second - coords.second, 2) + pow(intersections.at(i).first - coords.first, 2));
        if (distance < closestDistance)
        {
            closestDistance = distance;
            closestIntersection = intersections.at(i);
        }
    }
    return closestIntersection;
}

void LightSource::calcIntersections(std::vector<std::array<float, 4>> &_walls)
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
        if (0 < t && t < 1 && u > 0 && u < 1)
        {
            intersection = calcIntersection();
            intersections.push_back(intersection);
        }
    }
}
void LightSource::emitLight(UI &ui, std::vector<std::array<float, 4>> &_walls)
{
    ui.setDrawColor(255, 255, 255, 200);
    for (int i = 0; i < 360; i = i + 1)
    {
        x = coords.first;
        y = coords.second;
        ang = i * pi / 180;
        // coords outside of screen (needed for calculation of intersection!)
        c1 = x + 10000*cos(ang); 
        c2 = y + 10000*sin(ang);
          
        calcIntersections(_walls);
        intersection = getClosestIntersection();
        if (!intersections.empty())
        {
            // drawing 50 pixels away from center to not have bright overlapping
            ui.drawLine(x+cos(ang)*50, y+sin(ang)*50, intersection.first, intersection.second);
        }

        // clear intersections
        while (!intersections.empty())
        {
           intersections.pop_back();
        }
        intersection = {0, 0};
    }
}