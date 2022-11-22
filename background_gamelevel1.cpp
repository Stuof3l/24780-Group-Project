//
//  background.cpp
//  background
//
//  Created on 11/12/22.
//  Contributors: Jiayu Li, Kaiyuan Zhang
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"
using namespace std;

// Constant variables
const double PI=3.1415927;
const int width = 800;
const int height = 600;

// Some basic graphics
void DrawSolidCircle(double cx, double cy, double R)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<64; ++i)
    {
        double a = (double)i * PI * 2.0/64.0;
        double s = sin(a);
        double c = cos(a);
        glVertex2d(cx+c*R,cy+s*R);
    }
    glEnd();
}

void DrawHollowCircle(double cx, double cy, double R)
{
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<64; ++i)
    {
        double a = (double)i * PI * 2.0/64.0;
        double s = sin(a);
        double c = cos(a);
        glVertex2d(cx+c*R,cy+s*R);
    }
    glEnd();
}

void DrawSolidRect(double bottomX, double bottomY, double recWid, double recHei)
{
    glBegin(GL_POLYGON);
    glVertex2d(bottomX, bottomY);
    glVertex2d(bottomX, bottomY-recHei);
    glVertex2d(bottomX+recWid, bottomY-recHei);
    glVertex2d(bottomX+recWid, bottomY);
    glEnd();
}

void DrawHollowRect(double bottomX, double bottomY, double recWid, double recHei)
{
    glBegin(GL_LINE_LOOP);
    glVertex2d(bottomX, bottomY);
    glVertex2d(bottomX, bottomY-recHei);
    glVertex2d(bottomX+recWid, bottomY-recHei);
    glVertex2d(bottomX+recWid, bottomY);
    glEnd();
}

void DrawTriangle(double leftX, double rightX, double centerX, double topY, double bottomY)
{
    glBegin(GL_POLYGON);
    glVertex2d(leftX, bottomY);
    glVertex2d(centerX, topY);
    glVertex2d(rightX, bottomY);
    glEnd();
}

void DrawLine(double x1, double x2, double y1, double y2)
{
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

// Castle decorations
class Coin
{
public:
    friend class Level1;
    friend class level2;
    friend class level3;
    double coinX, coinY;
    int coinR;
    int coinState; // The state of the coin can show whether it is hitted the main character or not.
    void DrawCoin(double coinX, double coinY, int coinR, int coinState);
};

void Coin::DrawCoin(double coinX, double coinY, int coinR, int coinState)
{
    if (coinState == 1)
    {
        int r = 255;
        int g = rand()%75+170;
        int b = 0;
        // Outer circle of the coin
        glColor3ub(r, g, b);
        DrawSolidCircle(coinX, coinY, coinR);
        glLineWidth(3);
        glColor3ub(184,134,11);
        DrawHollowCircle(coinX, coinY, coinR);
        // Inter circle of the coin
        DrawHollowCircle(coinX, coinY, coinR*0.7);
        // "$" symbol
        glRasterPos2i(coinX-7, coinY+10);
        YsGlDrawFontBitmap16x20("$");
    }
}
 
class Stone // I change the name of "Box" to "Stone"
{
public:
    friend class Level1;
    friend class level2;
    friend class level3;
    double stoneX, stoneY;
    int stoneLen;
    void DrawStone(double stoneX, double stoneY, int stoneLen);
};

void Stone::DrawStone(double stoneX, double stoneY, int stoneLen)
{
    double interRecLen = stoneLen*0.6;
    double marginRecLen = (stoneLen - interRecLen) * 0.5;
    // Solid rectangle of the stone
    glColor3ub(192,192,192);
    DrawSolidRect(stoneX, stoneY, stoneLen, stoneLen);
    glColor3ub(220,220,220);
    DrawSolidRect(stoneX+marginRecLen, stoneY-marginRecLen, interRecLen, interRecLen);
    //  Patterns of the stone
    glColor3ub(128,128,128);
    glLineWidth(3);
    DrawHollowRect(stoneX, stoneY, stoneLen, stoneLen);
    DrawHollowRect(stoneX+marginRecLen, stoneY-marginRecLen, interRecLen, interRecLen);
    DrawLine(stoneX, stoneX+marginRecLen, stoneY, stoneY-marginRecLen);
    DrawLine(stoneX, stoneX+marginRecLen, stoneY-stoneLen, stoneY+marginRecLen-stoneLen);
    DrawLine(stoneX+stoneLen, stoneX-marginRecLen+stoneLen, stoneY, stoneY-marginRecLen);
    DrawLine(stoneX+stoneLen, stoneX-marginRecLen+stoneLen, stoneY-stoneLen, stoneY+marginRecLen-stoneLen);
}

class Obstacle
{
public:
    friend class Level1;
    friend class level2;
    friend class level3;
    double obsX, obsY;
    void DrawObs1(double obsX, double obsY, int nObs1);
    void DrawObs2(double obsX, double obsY);
    void DrawObs3(double obsX, double obsY);
    // DrawObs4, DrawObs5, DrawObs6 ...
};

void Obstacle::DrawObs1(double obsX, double obsY, int nObs1)
{
    Stone obsS1[nObs1];
    for(int i=0; i<nObs1; i++)
    {
        obsS1[i].stoneLen = 50;
        obsS1[i].stoneX = obsX + obsS1[i].stoneLen*i;
        obsS1[i].stoneY = obsY;
        obsS1[i].DrawStone(obsS1[i].stoneX, obsS1[i].stoneY, obsS1[i].stoneLen);
    }
}

void Obstacle::DrawObs2(double obsX, double obsY)
{
    const int nObs2= 5;
    Stone obsS2[nObs2];
    for(int i=0; i<nObs2-2; i++)
    {
        obsS2[i].stoneLen = 50;
        obsS2[i].stoneX = obsX + obsS2[i].stoneLen*i;
        obsS2[i].stoneY = obsY;
        obsS2[i].DrawStone(obsS2[i].stoneX, obsS2[i].stoneY, obsS2[i].stoneLen);
    }
    for(int i=3; i<nObs2; i++)
    {
        obsS2[i].stoneLen = 50;
        obsS2[i].stoneX = obsX + obsS2[i].stoneLen*(i-2);
        obsS2[i].stoneY = obsY - obsS2[i].stoneLen;
        obsS2[i].DrawStone(obsS2[i].stoneX, obsS2[i].stoneY, obsS2[i].stoneLen);
    }
}

void Obstacle::DrawObs3(double obsX, double obsY)
{
    const int nObs2= 4;
    Stone obsS2[nObs2];
    for(int i=0; i<nObs2-1; i++)
    {
        obsS2[i].stoneLen = 50;
        obsS2[i].stoneX = obsX + obsS2[i].stoneLen*i;
        obsS2[i].stoneY = obsY;
        obsS2[i].DrawStone(obsS2[i].stoneX, obsS2[i].stoneY, obsS2[i].stoneLen);
    }

    obsS2[3].stoneLen = 50;
    obsS2[3].stoneX = obsX + obsS2[3].stoneLen;
    obsS2[3].stoneY = obsY - obsS2[3].stoneLen;
    obsS2[3].DrawStone(obsS2[3].stoneX, obsS2[3].stoneY, obsS2[3].stoneLen);
}

class Door
{
public:
    double doorX, doorY;
    int doorWid, doorHei;
    double doorSpeed;
    void DrawDoor(double doorX, double doorY, int doorWid, int doorHei);
    void MoveDoor(double doorX, double doorY, double doorSpeed);
};

class Level1 // Rooftop night
{
public:
    int treeX1 = width * 0.1;
    int treeX2 = width * 0.3;
    int treeX3 = width * 0.5;
    int treeX4 = width * 0.7;
    int treeX5 = width * 0.9;
    void DrawBackground();
    void DrawObstacle();
    void DrawCoin();
    void DrawMoon();
    void DrawTree(int treeX);
};

void Level1::DrawBackground()
{
    // Dark night background
    glColor3ub(72,61,139);
    DrawSolidRect(0, height, width, height);
}

void Level1::DrawObstacle()
{
    // Obstacles
    int stoneLen = 50;
    int nObsComponents1 = 4;
    int nObsComponents2 = 16;
    int nObs = 7;
    Obstacle obs[nObs];
    obs[0].obsX = stoneLen*3;
    obs[0].obsY = height*0.65;
    obs[1].obsX = width*0.6;
    obs[1].obsY = height*0.7;
    obs[2].obsX = stoneLen*5;
    obs[2].obsY = height-stoneLen;
    obs[3].obsX = 0;
    obs[3].obsY = height;
    obs[4].obsX = 0;
    obs[4].obsY = height-stoneLen;
    obs[5].obsX = stoneLen*13;
    obs[5].obsY = height-stoneLen;
    obs[6].obsX = stoneLen*7;
    obs[6].obsY = height*0.4;
    
    obs[0].DrawObs1(obs[0].obsX, obs[0].obsY, nObsComponents1);
    obs[1].DrawObs2(obs[1].obsX, obs[1].obsY);
    obs[2].DrawObs3(obs[2].obsX, obs[2].obsY);
    obs[3].DrawObs1(obs[3].obsX, obs[3].obsY, nObsComponents2);
    obs[2].DrawObs3(obs[4].obsX, obs[4].obsY);
    obs[2].DrawObs2(obs[5].obsX, obs[5].obsY);
    obs[6].DrawObs1(obs[6].obsX, obs[6].obsY, nObsComponents1);
}

void Level1::DrawCoin()
{
    int stoneLen = 50;
    // Coins
    const int nCoin= 6;
    Coin coin[nCoin];
    double gap = 0;
    for(auto &c : coin)
    {
        c.coinR = 20;
        c.coinState = 1;
    }
    coin[0].coinX = stoneLen*11.5;
    coin[0].coinY = height*0.87;
    coin[0].DrawCoin(coin[0].coinX, coin[0].coinY, coin[0].coinR, coin[0].coinState);
    coin[1].coinX = stoneLen*6.5;
    coin[1].coinY = height*0.52;
    coin[1].DrawCoin(coin[1].coinX, coin[1].coinY, coin[1].coinR, coin[0].coinState);
    coin[2].coinX = stoneLen*8.5;
    coin[2].coinY = height*0.27;
    coin[2].DrawCoin(coin[2].coinX, coin[2].coinY, coin[2].coinR, coin[0].coinState);
    coin[3].coinX = stoneLen*10.5;
    coin[3].coinY = height*0.27;
    coin[3].DrawCoin(coin[3].coinX, coin[3].coinY, coin[3].coinR, coin[0].coinState);
    coin[4].coinX = stoneLen*5.5;
    coin[4].coinY = height*0.79;
    coin[4].DrawCoin(coin[4].coinX, coin[4].coinY, coin[4].coinR, coin[0].coinState);
    coin[5].coinX = stoneLen*0.5;
    coin[5].coinY = height*0.79;
    coin[5].DrawCoin(coin[5].coinX, coin[5].coinY, coin[5].coinR, coin[0].coinState);
};

void Level1::DrawMoon()
{
    double moonX = width * 0.75;
    double moonY = height * 0.1;
    double moonR = 30;
    glColor3ub(255,248,220);
    DrawSolidCircle(moonX, moonY, moonR);
    glColor3ub(72,61,139);
    DrawSolidCircle(moonX+moonR*0.5, moonY, moonR);
}

void Level1::DrawTree(int treeX)
{
    double treeLen = 10;
    double treeY1 = height * 0.25;
    double treeY2 = height * 0.38;
    double treeY3 = height * 0.58;
    double treeY4 = height * 0.72;
    glColor3ub(32,178,170);
    DrawTriangle(treeX-treeLen*5, treeX+treeLen*5, treeX, treeY1, treeY2*1.15);
    DrawTriangle(treeX-treeLen*7, treeX+treeLen*7, treeX, (treeY2+treeY1)/2, treeY3);
    DrawTriangle(treeX-treeLen*9, treeX+treeLen*9, treeX, (treeY3+treeY2)/2, treeY4);
    DrawSolidRect(treeX-treeLen*1.5, height, treeLen*3, height*0.3);
}

class Level2
{

};

class Level3
{
    
};

// the main function is only for demonstration
int main(void)
{
    
    srand(time(NULL)); // set random number seed from time
    
    // Level1
    Level1 l1;
    
    FsOpenWindow(16,16,width,height,1);
    
    while(true)
    {
        FsPollDevice();
        auto key=FsInkey();
        // Quit when users press esc
        if(FSKEY_ESC==key)
        {
            break;
        }
  
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        // Draw Level 1 of the game
        l1.DrawBackground();
        l1.DrawTree(l1.treeX1);
        l1.DrawTree(l1.treeX2);
        l1.DrawTree(l1.treeX3);
        l1.DrawTree(l1.treeX4);
        l1.DrawTree(l1.treeX5);
        l1.DrawObstacle();
        l1.DrawCoin();
        l1.DrawMoon();
        
        FsSwapBuffers();
        FsSleep(10);
    }
    return 0;
}
    
