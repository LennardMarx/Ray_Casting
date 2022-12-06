#pragma once

#ifndef APPLE_H
#define APPLE_H

#include <array>

class LightSource
{
public:
    LightSource();
    ~LightSource();

    void setPosition(UI &, int, int);

    std::pair<int, int> getPosition();

    std::pair<float, float> calcIntersection();

    std::pair<float, float> getClosestIntersection();

    // bool checkIntersect(Border *);
    void calcIntersections(std::vector<std::array<float, 4>> &);

    void emitLight(UI &ui, std::vector<std::array<float, 4>> &);

private:
    float x, y, c1, c2;
    float x1, x2, x3, x4, y1, y2, y3, y4;
    float t, u, denom;
    std::pair<int, int> coords;
    float pi = 3.14159265358979323846;
    float ang;
    bool check = false;

    std::pair<float, float> intersection;
    std::pair<float, float> closestIntersection;
    float distance, lastDistance = 0, closestDistance;
    std::vector<std::pair<float, float>> intersections;
};

#endif