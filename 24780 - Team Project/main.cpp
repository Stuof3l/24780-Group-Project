//
//  main.cpp
//  24780 - Team Project
//

#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "fssimplewindow.h"
//#include "ysglfontdata.h"
//#include "yssimplesound.h"
//#include "yspng.h"
using namespace std;

enum game_states {
    WELCOME_PAGE,
    PLAY,
    PLAYER_DIED,
    GAME_END
};

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

void DrawWelcome();
void DrawBackground();
void DrawEnd();
void DrawPlayerDied();

int main() {
    game_states gameStates = WELCOME_PAGE;
    
    FsOpenWindow(300,300,WINDOWWIDTH,WINDOWHEIGHT,1);
    auto key=FsInkey();
    while(1) {
        FsPollDevice();
        key=FsInkey();
        
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        // testtest
        if (key == FSKEY_ESC) {
            break;
        } else if ((gameStates == WELCOME_PAGE || gameStates == PLAYER_DIED) && key == FSKEY_S) {
            DrawWelcome();
            gameStates = PLAY;
        } else if ((gameStates == WELCOME_PAGE || gameStates == PLAYER_DIED) && key == FSKEY_E) {
            DrawEnd();
            gameStates = GAME_END;
            break;
        }
        auto passed=FsPassedTime();
        
        if(gameStates == PLAYER_DIED) {
            DrawPlayerDied();
        }
       
        FsSwapBuffers();
        FsSleep(25);
    }

    return 0;
}
