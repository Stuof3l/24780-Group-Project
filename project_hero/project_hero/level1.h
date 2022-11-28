#pragma once
#include "Obstacle.h"
class Level1
{
public:
    int treeX1 = 800 * 0.1;
    int treeX2 = 800 * 0.3;
    int treeX3 = 800 * 0.5;
    int treeX4 = 800 * 0.7;
    int treeX5 = 800 * 0.9;
    void DrawBackground();
    void DrawObstacle();
    void DrawMoon();
    void DrawTree(int treeX);
};

