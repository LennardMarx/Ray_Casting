#pragma once

#ifndef APPLE_H
#define APPLE_H

class LightSource
{
public:
    LightSource();
    ~LightSource();

    void setPosition(UI &, int, int);

    std::pair<int, int> getPosition();

    std::pair<double, double> calcIntersection();

    std::pair<float, float> getClosestIntersection();

    // bool checkIntersect(Border *);
    void calcIntersections(std::vector<std::array<int, 4>>);

    void emitLight(UI &ui, std::vector<std::array<int, 4>> &);

private:
    int x, y, c1, c2;
    int x1, x2, x3, x4, y1, y2, y3, y4;
    double t, u, denom;
    std::pair<int, int> coords;
    double pi = 3.14159265358979323846;
    double ang;
    Border border;
    bool check = false;

    std::pair<double, double> intersection;
    std::pair<double, double> closestIntersection;
    float distance, lastDistance = 0;
    std::vector<std::pair<double, double>> intersections;
};

#endif