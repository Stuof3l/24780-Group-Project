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

enum game_states {
    WELCOME_PAGE,
    PLAY,
    PLAYER_DIED,
    GAME_END
};

enum font_size {
    SMALL,
    MEDIUM,
    LARGE
};

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

void DrawWelcome();
void DrawBackground(game_states gameState);
void DrawEnd();
void DrawPlayerDied();
void DrawWords(string str, int x, int y, font_size fontSize);
void DrawBox(double x, double y, double xLength, double yLength);
const char* SelectMusic(game_states gameStates);

int main() {
    game_states gameStates = WELCOME_PAGE;
    FsChangeToProgramDir();
    FsOpenWindow(300,300,WINDOWWIDTH,WINDOWHEIGHT,1);
    
    
    const char* mscName = SelectMusic(gameStates);
    YsSoundPlayer player;
    YsSoundPlayer::SoundData wav;
    wav.LoadWav(mscName);
    player.Start();
    player.PlayOneShot(wav);
    
    auto key=FsInkey();
//    while(YSTRUE==player.IsPlaying(wav)) {
    while(1) {
        player.KeepPlaying();
        FsPollDevice();
        key=FsInkey();
//        if(key != FSKEY_NULL) {
//            const char* mscKey = "keypress.wav";
//            wav.LoadWav(mscKey);
//            player.Start();
//            player.PlayOneShot(wav);
//        }
        if (key == FSKEY_ESC) {
           // end game
            break;
        } else if(gameStates == PLAY) {
            if(key == FSKEY_UP) {
                
            } else if (key == FSKEY_DOWN) {
                
            } else if (key == FSKEY_LEFT) {
                
            } else if (key == FSKEY_RIGHT) {
                
            }
            
            // if the player died, revise later on
            gameStates = PLAYER_DIED;
            mscName = SelectMusic(gameStates);
            wav.LoadWav(mscName);
            player.Start();
            player.PlayOneShot(wav);
            
        } else if ((gameStates == WELCOME_PAGE || gameStates == PLAYER_DIED) && key == FSKEY_S) {
            gameStates = PLAY;
            // play the game
        } else if ((gameStates == WELCOME_PAGE || gameStates == PLAYER_DIED) && key == FSKEY_E) {
            gameStates = GAME_END;
            player.End(); // does not work
        } else if (gameStates ==  GAME_END) {
            DrawEnd();
        } else if (gameStates == WELCOME_PAGE || gameStates == PLAYER_DIED) {
            DrawWelcome();
        }
        
        if(gameStates == PLAYER_DIED) {
            DrawPlayerDied();
        }
       
        FsSwapBuffers();
        FsSleep(25);
    }
    player.End();
    return 0;
}

const char* SelectMusic(game_states gameStates) {
    const char* mscName;
    if(gameStates == WELCOME_PAGE) {
        mscName = "pianomoment.wav";
    } else if (gameStates == PLAYER_DIED || gameStates == PLAY) {
        mscName = "littleidea.wav";
    } else if (gameStates == GAME_END) {
        mscName = "";
    } else {
        mscName = "ERROR";
        cout << "Error in game_states\n";
    }
    return mscName;
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

void DrawWelcome() {
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    DrawBackground(WELCOME_PAGE);
    DrawBox(170, 140, 460, 70);
    DrawWords("CASTLE CRASHER", 200, 200, LARGE);
    DrawBox(240, 360, 350, 50);
    DrawWords("Press S to Start", 260, 400, MEDIUM);
    DrawBox(240, 410, 350, 50);
    DrawWords("Press E to End", 270, 450, MEDIUM);
}

void DrawPlayerDied() {
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    DrawBackground(PLAYER_DIED);
    DrawBox(250, 130, 300, 70);
    DrawWords("YOU DIED", 290, 190, LARGE);
    DrawBox(240, 360, 350, 50);
    DrawWords("Press S to Start", 260, 400, MEDIUM);
    DrawBox(240, 410, 350, 50);
    DrawWords("Press E to End", 270, 450, MEDIUM);
}

void DrawEnd() {
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    DrawBackground(GAME_END);
    DrawBox(330, 130, 120, 70);
    DrawWords("BYE", 350, 190, LARGE);
    DrawBox(230, 360, 370, 50);
    DrawWords("Press ESC to quit", 250, 400, MEDIUM);
    
}

void DrawBox(double x, double y, double xLength, double yLength) {
    glColor3ub(192,192,192);
    glBegin(GL_QUADS);
    glVertex2d(x, y);
    glVertex2d(x, y+yLength);
    glVertex2d(x+xLength, y + yLength);
    glVertex2d(x+xLength, y);
    glEnd();
    
    glColor3ub(128,128,128);
    glLineWidth(7);
    glBegin(GL_LINE_LOOP);
    glVertex2d(x, y);
    glVertex2d(x, y+yLength);
    glVertex2d(x+xLength, y + yLength);
    glVertex2d(x+xLength, y);
    glEnd();
}

void DrawBackground(game_states gameState) {
    YsRawPngDecoder png;
    const char* imgName;
    if(gameState == WELCOME_PAGE) {
        imgName = "WelcomeImage.png";
    } else if (gameState == PLAYER_DIED) {
        imgName = "PlayerDied.png";
    } else if (gameState == GAME_END) {
        imgName = "GameEnd.png";
    }
    png.Decode(imgName);
    png.Flip();
    if(0==png.wid || 0==png.hei)
    {
        printf("Failed to load image.\n");
        return;
    }
    int w,h;
    FsGetWindowSize(w,h);
    glRasterPos2i(0,double(h-1));
    glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
}
