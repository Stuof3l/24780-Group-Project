// project_hero.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"
#include "Drawer.h"
#include "Obstacle.h"
#include "level1.h"
using namespace std;

const double PI = 3.1415927;

int main()
{
    std::cout << "Hello World!\n";
    FsOpenWindow(16, 16, 800, 600, 1);
    Level1 l1;
    for (;;) {
        FsPollDevice();
        auto key = FsInkey();
        // Quit when users press esc
        if (FSKEY_ESC == key)
        {
            break;
        }
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        l1.DrawBackground();
        l1.DrawTree(l1.treeX1);
        l1.DrawTree(l1.treeX2);
        l1.DrawTree(l1.treeX3);
        l1.DrawTree(l1.treeX4);
        l1.DrawTree(l1.treeX5);
        l1.DrawObstacle();
        l1.DrawMoon();
        FsSwapBuffers();
        FsSleep(10);
    }
    return 0;
}
