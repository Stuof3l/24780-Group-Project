#include "background.h"

const int width = 800;
const int height = 600;
const int backgroundLen = 100;

void DrawMoon()
{
    double moonX = width * 0.75;
    double moonY = height * 0.1;
    double moonR = 30;
    glColor3ub(255, 248, 220);
    DrawSolidCircle(moonX, moonY, moonR);
    glColor3ub(72, 61, 139);
    DrawSolidCircle(moonX + moonR * 0.5, moonY, moonR);
}

void DrawTree(int treeX)
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

// rooftop view
void background::DrawBackground1()
{
    // Dark night background
    int treeX1 = 800 * 0.1;
    int treeX2 = 800 * 0.3;
    int treeX3 = 800 * 0.5;
    int treeX4 = 800 * 0.7;
    int treeX5 = 800 * 0.9;
    glColor3ub(72, 61, 139);
    DrawSolidRect(0, height, width, height);
    DrawMoon();
    DrawTree(treeX1);
    DrawTree(treeX2);
    DrawTree(treeX3);
    DrawTree(treeX4);
    DrawTree(treeX5);
}

// checkerboard view
void background::DrawBackground2()
{
    // Dark interior castle background
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<7; j++)
        {
            if((i%2==0 && j%2!=0) || (i%2!=0 && j%2==0) )
            {
                glColor3ub(47,79,79);
            }
            else
            {
                glColor3ub(0,128,128);
            }
            DrawSolidRect(backgroundLen*i, backgroundLen*j, backgroundLen, backgroundLen);
        }
    }
}

// column view
void background::DrawBackground3()
{
    // Dark interior castle background
    glColor3ub(230,230,250);
    DrawSolidRect(0, height, width, height);
    int circleR = 100;
    for(int i=0; i<4; i++)
    {
        glColor3ub(112,128,144);
        DrawSolidCircle(circleR*1.5+circleR*2.5*i, circleR*2, circleR);
        glColor3ub(70,130,180);
        DrawHollowCircle(circleR*1.5+circleR*2.5*i, circleR*2, circleR);
        glColor3ub(112,128,144);
        DrawSolidRect(circleR*0.5+circleR*2.5*i, height, circleR*2, height-circleR*2);
        glColor3ub(230,230,250);
        DrawSolidRect(circleR*2.5*i-circleR*0.05, height, circleR*0.6, circleR*0.6);
        DrawSolidRect(circleR*2.5*i-circleR*0.1, height, circleR*0.7, circleR*0.4);
        DrawSolidRect(circleR*2.5*i-circleR*0.1, circleR*2, circleR*0.7, circleR*0.5);
        glColor3ub(70,130,180);
        glLineWidth(3);
        DrawHollowRect(circleR*2.5*i-circleR*0.05, height, circleR*0.6, circleR*0.6);
        DrawHollowRect(circleR*2.5*i-circleR*0.1, height, circleR*0.7, circleR*0.4);
        glColor3ub(230,230,250);
        DrawSolidRect(circleR*2.5*i-circleR*0.1, height, circleR*0.7, circleR*0.4);
        glColor3ub(70,130,180);
        DrawHollowRect(circleR*2.5*i-circleR*0.1, circleR*2, circleR*0.7, circleR*0.5);
        for(int j=0; j<4; j++)
        {
            DrawHollowRect(circleR*2.5*i+circleR*0.125*j, height-circleR*0.6, circleR*0.125, height-circleR*2.6);
        }
    }
}

// big window view
void background::DrawBackground4()
{
    int marginLen = 200;
    int marginFlag = 10;
    int curtainR = 40;
    // Dark interior castle background
    glColor3ub(255,228,225);
    DrawSolidRect(0, height, width, height);
    glColor3ub(220,20,60);
    DrawSolidRect(0, marginLen*0.3, width, marginLen*0.3);
    for(int i=0; i<21; i++)
    {
        DrawSolidCircle(0+curtainR*i, marginLen*0.3, curtainR);
    }
    DrawSolidRect(marginLen-marginLen*0.1, height, marginLen*0.2, height);
    DrawSolidRect(marginLen*3-marginLen*0.1, height, marginLen*0.2, height);
    glColor3ub(255,215,0);
    DrawSolidRect(marginLen-marginLen*0.25-marginFlag, height*0.5, marginLen*0.5+marginFlag*2, height*0.5);
    DrawSolidRect(marginLen*3-marginLen*0.25-marginFlag, height*0.5, marginLen*0.5+marginFlag*2, height*0.5);
    DrawTriangle(marginLen-marginLen*0.25-marginFlag, marginLen+marginLen*0.25+marginFlag, marginLen, height*0.55+marginFlag, height*0.5);
    DrawTriangle(marginLen*3-marginLen*0.25-marginFlag, marginLen*3+marginLen*0.25+marginFlag, marginLen*3, height*0.55+marginFlag, height*0.5);
    glColor3ub(220,20,60);
    DrawSolidRect(marginLen-marginLen*0.25, height*0.5, marginLen*0.5, height*0.5);
    DrawSolidRect(marginLen*3-marginLen*0.25, height*0.5, marginLen*0.5, height*0.5);
    DrawTriangle(marginLen-marginLen*0.25, marginLen+marginLen*0.25, marginLen, height*0.55, height*0.5);
    DrawTriangle(marginLen*3-marginLen*0.25, marginLen*3+marginLen*0.25, marginLen*3, height*0.55, height*0.5);
    glColor3ub(147,112,219);
    DrawTriangle(marginLen*1.5, marginLen*2.5, marginLen*2, marginLen*0.8, marginLen);
    DrawSolidRect(marginLen*1.5, height, marginLen, height-marginLen);
    for(int j=0; j<3; j++)
    {
        glColor3ub(224,255,255);
        DrawSolidRect(marginLen*1.55, height-marginLen*0.05-marginLen*0.65*j, marginLen*0.425, marginLen*0.6);
        DrawSolidRect(marginLen*2.025, height-marginLen*0.05-marginLen*0.65*j, marginLen*0.425, marginLen*0.6);
    }
}
