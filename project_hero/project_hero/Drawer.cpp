#include <iostream>
#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"
#include "Drawer.h"

const double PI = 3.1415927;
void DrawSolidCircle(double cx, double cy, double R)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 64; ++i)
    {
        double a = (double)i * PI * 2.0 / 64.0;
        double s = sin(a);
        double c = cos(a);
        glVertex2d(cx + c * R, cy + s * R);
    }
    glEnd();
}
void DrawHollowCircle(double cx, double cy, double R)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 64; ++i)
    {
        double a = (double)i * PI * 2.0 / 64.0;
        double s = sin(a);
        double c = cos(a);
        glVertex2d(cx + c * R, cy + s * R);
    }
    glEnd();
}

void DrawSolidRect(double bottomX, double bottomY, double recWid, double recHei)
{
    glBegin(GL_POLYGON);
    glVertex2d(bottomX, bottomY);
    glVertex2d(bottomX, bottomY - recHei);
    glVertex2d(bottomX + recWid, bottomY - recHei);
    glVertex2d(bottomX + recWid, bottomY);
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

void DrawHollowRect(double bottomX, double bottomY, double recWid, double recHei)
{
    glBegin(GL_LINE_LOOP);
    glVertex2d(bottomX, bottomY);
    glVertex2d(bottomX, bottomY - recHei);
    glVertex2d(bottomX + recWid, bottomY - recHei);
    glVertex2d(bottomX + recWid, bottomY);
    glEnd();
}


void squareTextureMap(YsRawPngDecoder& png, double x, double y, double h, double w) {

    GLuint textID;
    glGenTextures(1, &textID);
    glBindTexture(GL_TEXTURE_2D, textID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png.wid, png.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4d(1.0, 1.0, 1.0, 1.0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0);
    glBindTexture(GL_TEXTURE_2D, textID);
    glBegin(GL_QUADS);
    glTexCoord2d(1.0, 1.0); glVertex2i(x + w, y + h);
    glTexCoord2d(0.0, 1.0); glVertex2i(x, y + h);
    glTexCoord2d(0.0, 0.0); glVertex2i(x, y);
    glTexCoord2d(1.0, 0.0); glVertex2i(x + w, y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
}
