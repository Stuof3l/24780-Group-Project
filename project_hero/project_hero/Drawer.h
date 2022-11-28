#pragma once
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"
#include "yspng.h"

#ifndef DRAWER
#define DRAWER
#endif

void DrawSolidCircle(double cx, double cy, double R);
void DrawHollowCircle(double cx, double cy, double R);
void DrawSolidRect(double bottomX, double bottomY, double recWid, double recHei);
void DrawTriangle(double leftX, double rightX, double centerX, double topY, double bottomY);
void DrawLine(double x1, double x2, double y1, double y2);
void DrawHollowRect(double bottomX, double bottomY, double recWid, double recHei);
void squareTextureMap(YsRawPngDecoder& png, double x, double y, double h, double w);
