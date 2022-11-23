#include "level1.h"
const int width = 800;
const int height = 600;
void Level1::DrawBackground()
{
    // Dark night background
    glColor3ub(72, 61, 139);
    DrawSolidRect(0, height, width, height);
}

void Level1::DrawObstacle()
{
    // Obstacles
    int stoneLen = 50;
    const int nObsComponents1 = 4;
    const int nObsComponents2 = 16;
    const int nObs = 7;
    Obstacle obs[nObs];
    obs[0].obsX = stoneLen * 3;
    obs[0].obsY = height * 0.65;
    obs[1].obsX = width * 0.6;
    obs[1].obsY = height * 0.7;
    obs[2].obsX = stoneLen * 5;
    obs[2].obsY = height - stoneLen;
    obs[3].obsX = 0;
    obs[3].obsY = height;
    obs[4].obsX = 0;
    obs[4].obsY = height - stoneLen;
    obs[5].obsX = stoneLen * 13;
    obs[5].obsY = height - stoneLen;
    obs[6].obsX = stoneLen * 7;
    obs[6].obsY = height * 0.4;

    //obs[0].DrawObs1(obs[0].obsX, obs[0].obsY, nObsComponents1);
    //obs[1].DrawObs2(obs[1].obsX, obs[1].obsY);
    //obs[2].DrawObs3(obs[2].obsX, obs[2].obsY);
    //obs[3].DrawObs1(obs[3].obsX, obs[3].obsY, nObsComponents2);
    obs[3].DrawObs_Line(obs[3].obsX, obs[3].obsY);
    //obs[2].DrawObs3(obs[4].obsX, obs[4].obsY);
    //obs[2].DrawObs2(obs[5].obsX, obs[5].obsY);
    //obs[6].DrawObs1(obs[6].obsX, obs[6].obsY, nObsComponents1);
}


void Level1::DrawMoon()
{
    double moonX = width * 0.75;
    double moonY = height * 0.1;
    double moonR = 30;
    glColor3ub(255, 248, 220);
    DrawSolidCircle(moonX, moonY, moonR);
    glColor3ub(72, 61, 139);
    DrawSolidCircle(moonX + moonR * 0.5, moonY, moonR);
}

void Level1::DrawTree(int treeX)
{
    double treeLen = 10;
    double treeY1 = height * 0.25;
    double treeY2 = height * 0.38;
    double treeY3 = height * 0.58;
    double treeY4 = height * 0.72;
    glColor3ub(32, 178, 170);
    DrawTriangle(treeX - treeLen * 5, treeX + treeLen * 5, treeX, treeY1, treeY2 * 1.15);
    DrawTriangle(treeX - treeLen * 7, treeX + treeLen * 7, treeX, (treeY2 + treeY1) / 2, treeY3);
    DrawTriangle(treeX - treeLen * 9, treeX + treeLen * 9, treeX, (treeY3 + treeY2) / 2, treeY4);
    DrawSolidRect(treeX - treeLen * 1.5, height, treeLen * 3, height * 0.3);
}