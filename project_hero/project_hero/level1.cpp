#include "level1.h"

const int width = 800;
const int height = 600;

Level1::Level1()
{
}

void Level1::DrawObstacle()
{
    // Obstacles
    int stoneLen = 50;
    const int nObsComponents1 = 4;
    const int nObsComponents2 = 16;
    const int nObs = 7;
    Obstacle obs[nObs];
    obs[0].obsX = stoneLen * 5;
    obs[0].obsY = height - stoneLen;
    obs[1].obsX = 0;
    obs[1].obsY = height - stoneLen;
    obs[2].obsX = 0;
    obs[2].obsY = height;
    obs[3].obsX = stoneLen * 13;
    obs[3].obsY = height - stoneLen;

    obs[0].DrawObs3(obs[0].obsX, obs[0].obsY);
    obs[1].DrawObs3(obs[1].obsX, obs[1].obsY);
    obs[2].DrawObs1(obs[2].obsX, obs[2].obsY);
    obs[3].DrawObs2(obs[3].obsX, obs[3].obsY);

}

void Level1::DrawBackground()
{
    background bg1;
    bg1.DrawBackground4();
}
