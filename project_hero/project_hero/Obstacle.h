#pragma once
#include "fssimplewindow.h"
#include "Drawer.h"
class Stone
{
public:
    friend class Level1;
    friend class level2;
    friend class level3;
    double stoneX, stoneY;
    int stoneLen;
    void DrawStone(double stoneX, double stoneY, int stoneLen);
};

class Obstacle
{
public:
    friend class Level1;
    friend class level2;
    friend class level3;
    double obsX, obsY;
    void DrawObs2(double obsX, double obsY);
    void DrawObs3(double obsX, double obsY);
    void DrawObs_Line(double obsX, double obsY);
    // DrawObs4, DrawObs5, DrawObs6 ...
};