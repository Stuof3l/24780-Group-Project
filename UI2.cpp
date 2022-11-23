//
//  UI2.cpp
//  gameUI
//
//  Created by  Jasmine on 11/22/22.
//

#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"
#include "yspng.h"

using namespace std;
enum font_size {
    SMALL,
    MEDIUM,
    LARGE
};

//char* h1 = "heart1.png";
//char* h2 = "heart2.png";
//char* h0 = "heart0.png";
const int fileNum = 3;
const int heartNum = 5;

int wl = 800;
int ww = 600;

GLuint texID[fileNum];
YsRawPngDecoder png[fileNum];

class Heart{
public:
    int wid, hei;
    int heartState;// 2= full; 1 = half; 0 = empty
    double x,y;//coordinates of heart
    
    void generate(double x1, double y1);
    void addHeartState();
    void loseHeartState();
    void setPng();
    void drawImage();

};

void Heart::generate(double x1, double y1){
    x = x1;
    y = y1;
    heartState = 2;
    setPng();
    
}


void Heart::addHeartState(){
    if (heartState < 2){
        heartState++;
        setPng();
        
    }
}

void Heart::loseHeartState(){
    if (heartState > 0){
        heartState--;
        setPng();
        
    }
}

//void Heart::drawImage(){
//    glRasterPos2i(x,y);
//    glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
//}

void Heart::drawImage(){
//    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4d(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);  // Begin using texture mapping

    glBindTexture(GL_TEXTURE_2D, texID[heartState]);

    glBegin(GL_QUADS);

    glTexCoord2d(0.0, 0.0);
    glVertex2d(x, y);

    glTexCoord2d(1.0, 0.0);
    glVertex2d(x+wid, y);

    glTexCoord2d(1.0, 1.0);
    glVertex2d(x+wid, y+hei);

    glTexCoord2d(0.0, 1.0);
    glVertex2d(x, y+hei);

    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    
}

void Heart::setPng(){
    wid = png[heartState].wid /6;
    hei = png[heartState].hei /6;
}

void DrawRect(int x1,int y1,int x2,int y2,int fill, int r, int g, int b)
{
    glColor3ub(r,g,b);
    if(0!=fill)
    {
        glBegin(GL_QUADS);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }

    glVertex2i(x1,y1);
    glVertex2i(x2,y1);
    glVertex2i(x2,y2);
    glVertex2i(x1,y2);

    glEnd();
}

void DrawWords(string str, int x, int y, font_size fontSize) {
    const char* charStr = str.c_str();
    glColor3ub(0, 0, 0);
    glRasterPos2i(x, y);
    if(fontSize == SMALL) {
        YsGlDrawFontBitmap16x20(charStr);
    } else if(fontSize == MEDIUM) {
        YsGlDrawFontBitmap20x32(charStr);
    } else {
        YsGlDrawFontBitmap28x44(charStr);
    }
}

int main(){
    FsChangeToProgramDir();
   
    png[0].Decode("heart0.png");
    png[1].Decode("heart1.png");
    png[2].Decode("heart2.png");
    printf("%d %d\n", png[0].wid,png[0].hei);
    printf("%d %d\n", png[1].wid,png[1].hei);
    printf("%d %d\n", png[2].wid,png[2].hei);
    
    FsOpenWindow(300,300,wl,ww,1);
    
    
    int score = 0;
    long long int tStart;
    long long int tCur;
    long long int tGap;
    
    tStart = FsSubSecondTimer();
    
    for (int i = 0; i < fileNum ; i++)
    {
        glGenTextures(1,&texID[i]);  // Reserve one texture identifier
        glBindTexture(GL_TEXTURE_2D, texID[i]);  // Making the texture identifier current (or bring it to the deck)

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D
        (GL_TEXTURE_2D,
            0,    // Level of detail
            GL_RGBA,
            png[i].wid,
            png[i].hei,
            0,    // Border width, but not supported and needs to be 0.
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            png[i].rgba);
        
        png[i].Flip();
    }
    
    Heart hearts[heartNum];
    for(int i = 0; i < heartNum; i++){
        auto &h = hearts[i];
        h.generate(30 + i*40, 20);
    }
    
    FsPollDevice();
    while(1){
        FsPollDevice();
        auto key= FsInkey();
        if(key == FSKEY_ESC){
            break;
        }
        if(key == FSKEY_UP){
            
            for(int i = 0; i < heartNum; i ++){
                if(hearts[i].heartState != 2){
                    hearts[i].addHeartState();
                    score++;
                    break;
                }
            }
        }
        if(key == FSKEY_DOWN){
            for(int i = heartNum -1; i >= 0; i --){
                if(hearts[i].heartState != 0){
                    hearts[i].loseHeartState();
                    if(score > 0){
                        score --;
                    }
                    break;
                }
            }
        }
        
        // draw backgournd
        DrawRect(0, 0, wl, ww, 1,255,255,255);
        
        //draw hearts
        for(int i = 0; i < heartNum; i++){
            hearts[i].drawImage();
        }
        
        //draw score
        std::string temp = std::to_string(score);
        DrawWords(temp, 250, 45, SMALL);
       
        //draw time
        tCur = FsSubSecondTimer();
        tGap = (tCur - tStart)/1000;
        std::string ttemp = std::to_string(tGap);
        DrawWords(ttemp, 750, 45, SMALL);
        
        FsSwapBuffers();
        FsSleep(25);
        
    }
    
    return 0;
    
}
