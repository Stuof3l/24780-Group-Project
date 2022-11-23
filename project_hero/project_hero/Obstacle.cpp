#include "Obstacle.h"

void Stone::DrawStone(double stoneX, double stoneY, int stoneLen)
{
    double interRecLen = stoneLen * 0.6;
    double marginRecLen = (stoneLen - interRecLen) * 0.5;
    // Solid rectangle of the stone
    glColor3ub(192, 192, 192);
    DrawSolidRect(stoneX, stoneY, stoneLen, stoneLen);
    glColor3ub(220, 220, 220);
    DrawSolidRect(stoneX + marginRecLen, stoneY - marginRecLen, interRecLen, interRecLen);
    //  Patterns of the stone
    glColor3ub(128, 128, 128);
    glLineWidth(3);
    DrawHollowRect(stoneX, stoneY, stoneLen, stoneLen);
    DrawHollowRect(stoneX + marginRecLen, stoneY - marginRecLen, interRecLen, interRecLen);
    DrawLine(stoneX, stoneX + marginRecLen, stoneY, stoneY - marginRecLen);
    DrawLine(stoneX, stoneX + marginRecLen, stoneY - stoneLen, stoneY + marginRecLen - stoneLen);
    DrawLine(stoneX + stoneLen, stoneX - marginRecLen + stoneLen, stoneY, stoneY - marginRecLen);
    DrawLine(stoneX + stoneLen, stoneX - marginRecLen + stoneLen, stoneY - stoneLen, stoneY + marginRecLen - stoneLen);
}


void Obstacle::DrawObs2(double obsX, double obsY)
{
    const int nObs2 = 5;
    Stone obsS2[nObs2];
    for (int i = 0; i < nObs2 - 2; i++)
    {
        obsS2[i].stoneLen = 50;
        obsS2[i].stoneX = obsX + obsS2[i].stoneLen * i;
        obsS2[i].stoneY = obsY;
        obsS2[i].DrawStone(obsS2[i].stoneX, obsS2[i].stoneY, obsS2[i].stoneLen);
    }
    for (int i = 3; i < nObs2; i++)
    {
        obsS2[i].stoneLen = 50;
        obsS2[i].stoneX = obsX + obsS2[i].stoneLen * (i - 2);
        obsS2[i].stoneY = obsY - obsS2[i].stoneLen;
        obsS2[i].DrawStone(obsS2[i].stoneX, obsS2[i].stoneY, obsS2[i].stoneLen);
    }
}

void Obstacle::DrawObs3(double obsX, double obsY)
{
    const int nObs2 = 4;
    Stone obsS2[nObs2];
    for (int i = 0; i < nObs2 - 1; i++)
    {
        obsS2[i].stoneLen = 50;
        obsS2[i].stoneX = obsX + obsS2[i].stoneLen * i;
        obsS2[i].stoneY = obsY;
        obsS2[i].DrawStone(obsS2[i].stoneX, obsS2[i].stoneY, obsS2[i].stoneLen);
    }

    obsS2[3].stoneLen = 50;
    obsS2[3].stoneX = obsX + obsS2[3].stoneLen;
    obsS2[3].stoneY = obsY - obsS2[3].stoneLen;
    obsS2[3].DrawStone(obsS2[3].stoneX, obsS2[3].stoneY, obsS2[3].stoneLen);
}
void Obstacle::DrawObs_Line(double obsX, double obsY) {
    Stone obsS1[16];
    for (int i = 0; i < 16; i++)
    {
        obsS1[i].stoneLen = 50;
        obsS1[i].stoneX = obsX + obsS1[i].stoneLen * i;
        obsS1[i].stoneY = obsY;
        obsS1[i].DrawStone(obsS1[i].stoneX, obsS1[i].stoneY, obsS1[i].stoneLen);
    }
}