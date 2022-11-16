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
    double obsX, obsY;
    void DrawObs1(double obsX, double obsY);
    void DrawObs2(double obsX, double obsY);
    void DrawObs3(double obsX, double obsY);
    // DrawObs4, DrawObs5, DrawObs6 ...
};
void Obstacle::DrawObs1(double obsX, double obsY)
{
    const int nObs1= 4;
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
//    glColor3ub(72,61,139);
//    DrawRect(0, height, width, height);
};

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
    
    // Coin
    const int nCoin= 4;
    Coin coin[nCoin];
    double gap = 0;
    for(auto &c : coin)
    {
        c.coinR = 20;
        c.coinState = 1;
        gap += width*0.1;
        c.coinX = width*0.1 + gap;
        c.coinY = height*0.2;
    }
    
    // Stone
    const int nStone= 4;
    Stone stone[nStone];
    double sGap = 0;
    for(auto &s : stone)
    {
        s.stoneLen = 50;
        sGap += width*0.1;
        s.stoneX = width*0.1 + sGap;
        s.stoneY = height*0.4;
    }
    
    // Obstacle
    const int nObs= 3;
    Obstacle obs[nObs];
    obs[0].obsX = width*0.2;
    obs[0].obsY = height*0.7;
    obs[1].obsX = width*0.6;
    obs[1].obsY = height*0.7;
    obs[2].obsX = width*0.5;
    obs[2].obsY = height*0.9;
    
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
        
        // Draw coins
        for(auto &c : coin)
        {
            c.DrawCoin(c.coinX, c.coinY, c.coinR, c.coinState);
        }
        
        // Draw stones
        for(auto &s : stone)
        {
            s.DrawStone(s.stoneX, s.stoneY, s.stoneLen);
        }

        // Draw obstacles
        obs[0].DrawObs1(obs[0].obsX, obs[0].obsY);
        obs[1].DrawObs2(obs[1].obsX, obs[1].obsY);
        obs[2].DrawObs3(obs[2].obsX, obs[2].obsY);
        
        FsSwapBuffers();
        FsSleep(10);
    }
    return 0;
}
    
